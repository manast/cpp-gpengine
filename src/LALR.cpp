/***************************************************************************
                          LALR.cpp  -  description
                          ------------------------
    begin                : Fri Jun 14 2002
    copyright            : (C) 2002 by Manuel Astudillo

 ***************************************************************************/

 /***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

 #include <assert.h>
 #include "LALR.h"
 

 LALR::LALR (const LALRStateTable *stateTable, const SymbolTable *symbolTable,
 const RuleTable *ruleTable, integer startState) {
   this->stateTable = stateTable;
   this->symbolTable = symbolTable;
   this->ruleTable = ruleTable;
   this->startState = startState;

   errorTab = NULL;
   nbrBackUpTokens = 10;
 }

 LALR::~LALR () {
   delete errorTab;

   // Clean the stack in case elements are still there
   // TODO: Investigate why there are elements in the stack if the parser worked nicely
   while (!symbolStack.empty()) {
      //   delete symbolStack.top(); 
         symbolStack.pop();
   }
   
 }

 /*!
 Initializes the parser.
 Call this function before calling buildParseTree()

 /sa buildParseTree();

 */
 void LALR::init (const vector <Token*> &tokens) {

   // Copy the tokens vector (maybe just having a reference to it is enough...)
   this->tokens = tokens;

   // Initialize stack (And clear it in case there still are elements there)
   while (!symbolStack.empty()) {
         //delete symbolStack.top();
         symbolStack.pop();
   }
   
   // Create the start symbol (maybe it is not needed to place it in both stack and reductionList
   // Maybe is enough to put it in the stack and then at the end of the parsing return the top
   // of the stack, which would possible be the desired reduction
   Symbol *startReduction;
   startReduction = new Symbol ();
   startReduction->state = startState;
   
   symbolStack.push (startReduction);

   currentState = startState;

   tokenIndex = 0;

   delete errorTab;
   errorTab = new ErrorTable();

   trim = false;
 }


 /*!
  Parse the tokens until it reduces a rule.

  /param trimReduction especifies trimming enable or disable. Trimming will
  simplify rules of the form: NonTerminal1 := Nonterminal2

  /return next reduction or NULL if error or test accepted

  /sa getResult (), parse ()
 */

 Symbol *LALR::nextReduction (bool trimReductions, bool reportOnlyOneError) {
   Action *actObj;
   Token *tok;
  
   int action;

   m_trimReductions = trimReductions;

   for (;tokenIndex < tokens.size();tokenIndex++) {
     // Save this tokens information for the error system.
     tok = tokens[tokenIndex];
     lastTerminal.symbol = tok->symbol;
     lastTerminal.image = tok->image;
     lastTerminal.line =  tok->line;
     lastTerminal.col = tok->col;

     // Get next action
     actObj = getNextAction (tokens[tokenIndex]->symbolIndex, currentState);
   
     // Test for errors
     if (actObj == NULL) {
       // Generate ERROR & recover pushing expected symbol in the stack
       // RECOVERING IS IN THE TODO LIST!
       // FOR THAT WE NEED A MECHANISM TO "ESTIMATE" THE NEXT TOKEN
       // Or use Burke-Fisher recovering algorithm
       
       // Create a symbol traceback vector.
       vector <Symbol*> traceback;
       vector <Symbol*> tmptokvector = symbolStack.get_vector();
       for (short k = tmptokvector.size()-1; k >= 0; k--) {
            traceback.push_back (tmptokvector[k]);
       }
       
       vector <wstring> expectedTokens = getPossibleTokens (currentState);
       // Add the error to the Error class.
       errorTab->addError (ERROR_PARSE, UNEXPECTED_TOKEN, prevReduction, &lastTerminal,
                           expectedTokens, traceback, 
                           tokens[tokenIndex]->line,
                           tokens[tokenIndex]->col);
       if (reportOnlyOneError) {
          reductionResult = REDUCTION_ERROR;
          return NULL;
       }
          
     } else {
       // Update Global Error recovery system
       if (action == ACTION_SHIFT) {
            updateBurkeFisher (createTerminal(tokens[tokenIndex]));
       }

       Symbol *rdc = parseToken (actObj, symbolStack, tokenIndex, currentState);
       if (rdc == NULL) {
           if (reductionResult != REDUCTION_TOKEN_SHIFT) {
            return NULL;
           } 
       } else {
            return rdc;
       }

        }
   }
   reductionResult = REDUCTION_ERROR;
   return NULL;
 }


 /*!
    Computes an Action object from the input parameters

    /param symbolIndex  the index in the symbol table that we want to match
    /param index the current state in the LALR state machine
    /return Action NULL if no action found for this symbol Index.
 */
 Action *LALR::getNextAction (integer symbolIndex, integer index) {
   for (integer i=0; i < stateTable->states[index].actions.size(); i++) {
     if (stateTable->states[index].actions[i].symbolIndex == symbolIndex) {
       return &stateTable->states[index].actions[i];
     }
   }
   return NULL;
 }

 vector<wstring> LALR::getPossibleTokens (integer index) {
   vector<wstring> tokenVector;
   for (integer i=0; i < stateTable->states[index].actions.size(); i++) {
     integer j = stateTable->states[index].actions[i].symbolIndex;
     if (symbolTable->symbols[j].kind == TERMINAL) {
        wstring tokenName = symbolTable->symbols[j].name;
        tokenVector.push_back (tokenName);
     }
   }
   return tokenVector;
 }

 /*!
   Builds a parse tree with reductions as nodes.
   Sets the Error object with the possible compiling errors.

  /sa getError(), getNextReduction()
 */
 Symbol *LALR::parse (const vector <Token*> &tokens, bool trimReductions, 
                      bool reportOnlyOneError) {
   init (tokens);
     
   Symbol *reduction;
   prevReduction = NULL;
   while (true) {
     reduction = nextReduction(trimReductions, reportOnlyOneError);
     if ((reduction == NULL) && ((getResult() == REDUCTION_ERROR) ||
        (getResult() == REDUCTION_TEXT_ACCEPTED))) {
            break;
     } else if (reduction) {
            prevReduction = reduction;
     }
   }

   if (getResult() == REDUCTION_TEXT_ACCEPTED) {
      return prevReduction;
   } else {
      return NULL;
   }
 }

 int LALR::getResult () {
     return reductionResult;
 }

 ErrorTable *LALR::getErrors() {
     return errorTab;
 }

 void LALR::printReductionTree (Symbol *reduction, int deep) {
 integer i;

 // print tabs
 for (i=0; i < deep; i++) {
   wprintf (L" ");
 }

 if (reduction == NULL) {
   wprintf (L"NULL\n");
   return;
 }

 if (reduction->type == NON_TERMINAL) {
    wprintf (symbolTable->symbols[reduction->symbolIndex].name.c_str());
    wprintf (L"\n");
 
    for (i=0; i < ((NonTerminal*) reduction)->children.size(); i++) {
        printReductionTree (((NonTerminal*)reduction)->children[i], deep+1);
    }
 } else {
    wprintf (((Terminal*)reduction)->symbol.c_str());
    wprintf (L":");
    wprintf (((Terminal*)reduction)->image.c_str());
    wprintf (L"\n");
 }
}

 void LALR::updateBurkeFisher (Symbol *symbol) {
    if (errorQueue.size() == nbrBackUpTokens) {
            errorStack.push (errorQueue.front());
            errorQueue.pop();
     }
     errorQueue.push (symbol);
 }


 Symbol *LALR::parseToken (Action *actObj, SymbolStack &theStack, int tokenIndex, 
     integer &currentState) {

     NonTerminal  *newNonTerminal;
     Terminal     *newTerminal;
     
     integer index, i;
     
     int action, target;
     
     action = actObj->action;
     target = actObj->target;
     
     switch (action) {
     /*
     Pushes current token into the stack
         */
     case ACTION_SHIFT:
         // Push current token on the stack
         currentState = target;
         
         currentLine = tokens[tokenIndex]->line;
         currentCol = tokens[tokenIndex]->col;
         
         tokens[tokenIndex]->state = target;
         
         // Create a terminal symbol and push it onto the stack
         newTerminal = createTerminal (tokens[tokenIndex]);
         
         theStack.push (newTerminal);
         reductionResult = REDUCTION_TOKEN_SHIFT;
         return NULL;
         break;
         
         /*
         Creates a new reduction. Pops all the terminals and non terminals
         for this rule and pushes the most left non terminal.
         */
     case ACTION_REDUCE:
         
         // Create a new Non Terminal (to represent this reduction)
         index = ruleTable->rules[target].symbolIndex;
         
         newNonTerminal = createNonTerminal (index, target);
         
         // If the rule has only a nonterminal then we dont create a reduction
         // node for this rule in the tree since its not usefull.
         // User can decide to simplify this by enabling the trimming
         if ((ruleTable->rules[target].symbols.size() == 1) &&
             (symbolTable->symbols[ruleTable->rules[target].symbols[0]].kind ==
             NON_TERMINAL) && m_trimReductions) {
             trim = true; 
             newNonTerminal->trimmed = true;
         } else {
             newNonTerminal->trimmed = false;
             trim = false;
         }
         
         // pop from the stack the tokens for the reduced rule
         // and store them in the NonTerminal as its sons.
         for (i=0; i < ruleTable->rules[target].symbols.size(); i++) {
             Symbol *s = theStack.top ();
             // If the symbol is trimmed we just pick up its children
             if (s->trimmed) {
                 assert (s->type == NON_TERMINAL);
                 NonTerminal *trimmedNT = (NonTerminal*) s;
                 
                 assert (trimmedNT->children.size() == 1);
                 newNonTerminal->children.push_front (trimmedNT->children[0]);
             } else {
                 newNonTerminal->children.push_front (s);
             }
             theStack.pop();
         }
         
         // Perform GOTO
         actObj = getNextAction (newNonTerminal->symbolIndex, theStack.top()->state);
         
         if ((actObj != NULL) && (actObj->action == ACTION_GOTO)) {
             currentState = actObj->target;
             newNonTerminal->state = currentState;
             
             // Push the reduced nonterminal in the stack
             theStack.push (newNonTerminal);
         } else {
             wprintf (L"Internal Error!!\n");
             reductionResult = REDUCTION_ERROR;
             return NULL;
         }
         
         reductionResult = REDUCTION_COMPLETED;
         return newNonTerminal;
         break;
         
         // This Action should never happen...
     case ACTION_GOTO:
         wprintf (L"Goto: %d", target);
         currentState = target;
         break;
         
     case ACTION_ACCEPT:
         reductionResult = REDUCTION_TEXT_ACCEPTED;
         return NULL;
         break;
     }
     return NULL;
 }
 
 Terminal *LALR::createTerminal (Token *tok) {
     Terminal *newTerminal;
     newTerminal = new Terminal();
     newTerminal->symbol = tok->symbol;
     newTerminal->image = tok->image;
     newTerminal->symbolIndex = tok->symbolIndex;
     newTerminal->state = tok->state;
     newTerminal->line = tok->line;
     newTerminal->col = tok->col;
     return newTerminal;
 }
 
 NonTerminal *LALR::createNonTerminal (int index, int target) {
     NonTerminal *newNonTerminal;
     newNonTerminal = new NonTerminal();
     
     newNonTerminal->symbolIndex = index;
     newNonTerminal->symbol = symbolTable->symbols [index].name;
     
     newNonTerminal->ruleIndex = ruleTable->rules[target].ruleIndex;
     newNonTerminal->line = currentLine;
     newNonTerminal->col = currentCol;
     
     return newNonTerminal;
 }
 
