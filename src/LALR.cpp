/***************************************************************************
                          LALR.cpp  -  description
                             -------------------
    begin                : Fri Jun 14 2002
    copyright            : (C) 2002 by Manuel Astudillo
    email                : d00mas@efd.lth.se
 ***************************************************************************/

 /***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

 #include "LALR.h"

 LALR::LALR (const LALRStateTable *stateTable, const SymbolTable *symbolTable,
 const RuleTable *ruleTable, integer startState) {
   this->stateTable = stateTable;
   this->symbolTable = symbolTable;
   this->ruleTable = ruleTable;
   this->startState = startState;

   error = NULL;
 }

 LALR::~LALR () {
   
   // Delete all the tokens
   for (int i=0; i < this->tokens.size(); i++) {
	   delete this->tokens[i];
   }

   for (i=0; i < this->tokensList.size(); i++) {
	   delete tokensList[i];
   }

   // delete the reduction tree
   for (i=0; i < this->reductionsList.size(); i++) {
	   delete reductionsList[i];
   }

   delete error;
 }



 /*!
 Initializes the parser.
 Call this function before calling buildParseTree()

 /sa buildParseTree();

 */
 void LALR::parse (const vector <Token*> &tokens) {
   int i;

   // First we clean the tokens and the tokensList vector
   for (i=0; i < this->tokens.size(); i++) {
	   delete this->tokens[i];
   }
   this->tokens.clear();

   for (i=0; i < this->tokensList.size(); i++) {
	   delete tokensList[i];
   }
   tokensList.clear();

    // delete the reduction tree
   for (i=0; i < this->reductionsList.size(); i++) {
	   delete reductionsList[i];
   }
   reductionsList.clear();

   // Initialize stack
   while (!tokenStack.empty()) {
         tokenStack.pop();
   }
   startReduction = new Reduction();
   reductionsList.push_back(startReduction);

   Token *firstToken = new Token();
   tokensList.push_back(firstToken);

   startReduction->tok = firstToken;
   firstToken->reduction = startReduction;

   firstToken->state = startState;
   tokenStack.push (firstToken);

   // We replicate all the tokens (to eliminate dependencies with other classes)
   for (i=0; i < tokens.size(); i++) {
	   this->tokens.push_back (tokens[i]->newInstance());
   }
 
   currentState = startState;
   currentReduction = NULL;

   oldReduction = NULL;

   tokenIndex = 0;

   delete error;
   error = new Error();
 }

 /*!
  Parses the tokens until it reduces a rule.

  /param trimReduction especifies trimming enable or disable. Trimming will
  simplify rules of the form: NonTerminal1 := Nonterminal2

  /return next reduction or NULL if error or test accepted

  /sa getResult (), buildParseTree ()
 */

 Reduction *LALR::nextReduction (bool trimReduction, bool reportOnlyOneError) {
   Action *actObj;
   Token *newToken;

   integer i;
   wchar_t errorMsg[512];

   int action, target;

   Reduction *newReduction;

   integer symIndex;

   for (;tokenIndex < tokens.size();tokenIndex++) {
     // Get next action
     actObj = getNextAction (tokens[tokenIndex]->symbolIndex, currentState);
     if (actObj == NULL) {
       // Generate ERROR & recover pushing expected symbol in the stack
       errorMsg[0] = 0;

       wchar_t *possibleTokens = getPossibleTokens (currentState);
       wcscat (errorMsg, L"Error parsing this token: ");
       wcscat (errorMsg, tokens[tokenIndex]->symbol);
       wcscat (errorMsg, L"\nExpected: ");
       wcscat (errorMsg, possibleTokens);
       delete [] possibleTokens;

       error->addError (ERROR_PARSE, errorMsg, prevReduction, tokens[tokenIndex]->line,
       tokens[tokenIndex]->col);
       if (reportOnlyOneError) {
          reductionResult = REDUCTION_ERROR;
          return NULL;
       }

     }
     else {
       action = actObj->action;
       target = actObj->target;

       if (DEBUG) wprintf (L"Action: %d\n", action);

       switch (action) {
         /*
           Pushes current token into the stack
         */
         case ACTION_SHIFT:
         if (DEBUG) {
           wprintf (L"Shifting: ");
           wprintf (tokens[tokenIndex]->symbol);
           wprintf ( L"\nGo to state:%d\n\n", target);
         }

         // Push current token on the stack
         currentState = target;

		 currentLine = tokens[tokenIndex]->line;
		 currentCol = tokens[tokenIndex]->col;

         tokens[tokenIndex]->state = currentState;

		 tokenStack.push (tokens[tokenIndex]);
         break;

         /*
            Creates a new reduction. Pops all the terminals and non terminals
            for this rule and pushes the most left non terminal.
         */
         case ACTION_REDUCE:
         if (DEBUG) {
           wprintf (L"Reducing...\n");
         }

         // Create a new token for this rule
         newToken = new Token();

		 // Save it in the token pool to release it later
		 tokensList.push_back(newToken);

         newToken->kind = SYMBOL_NON_TERMINAL;
         newToken->symbolIndex = ruleTable->rules[target].nonTerminal;

		 newToken->symbol = new wchar_t [wcslen(symbolTable->symbols
			 [newToken->symbolIndex].name)+1];
  	  	 newToken->image = new wchar_t [wcslen(symbolTable->symbols
			 [newToken->symbolIndex].name)+1];

		 wcscpy (newToken->symbol, symbolTable->symbols[newToken->symbolIndex].name);
		 wcscpy (newToken->image, symbolTable->symbols[newToken->symbolIndex].name);

		 newToken->line = currentLine;
		 newToken->col = currentCol;


         // If the rule has only a nonterminal then we dont create a reduction
         // node for this rule in the tree since its not usefull.
         // User can decide to simplfy this enabling the trimming
        // if (trimReduction) &&

        if ((ruleTable->rules[target].symbols.size() == 1) &&
        (symbolTable->symbols[ruleTable->rules[target].symbols[0]].kind ==
        SYMBOL_NON_TERMINAL) && trimReduction) {
          newReduction = NULL;
        } else {
          // Create a new Reduction
          newReduction = new Reduction();
		  reductionsList.push_back(newReduction);
          oldReduction = newReduction;
          newReduction->tok = newToken;
        }

         newToken->reduction = oldReduction;

         if (DEBUG) {
           wprintf (symbolTable->symbols[ruleTable->rules[target].nonTerminal].name);
           wprintf (L" = ");
         }

         // pop from the stack the tokens for the reduced rule
         // and store them in the reduction
         for (i=0; i < ruleTable->rules[target].symbols.size(); i++) {
           symIndex = tokenStack.top()->symbolIndex;
           if (newReduction != NULL) {
             newReduction->childs.push_front (tokenStack.top());
           }
           tokenStack.pop();
         }
         if (DEBUG) {
           for (i=0; i < ruleTable->rules[target].symbols.size(); i++) {

             if (newReduction != NULL) {
               symIndex = newReduction->childs[i]->symbolIndex;
             }
             wprintf (symbolTable->symbols[symIndex].name);
             wprintf (L" ");
           }
           wprintf (L"\n");
         }

         // Perform GOTO
         if (DEBUG) {
           wprintf (L"state: %d index: %d\n", tokenStack.top()->state, newToken->symbolIndex);
         }
         actObj = getNextAction (newToken->symbolIndex, tokenStack.top()->state);
         if ((actObj != NULL) && (actObj->action == ACTION_GOTO)) {
           if (DEBUG) wprintf (L"Go to state: %d\n\n", actObj->target);
           currentState = actObj->target;
           newToken->state = currentState;

           // Push the reduced nonterminal in the stack
           tokenStack.push (newToken);
         } else {
           wprintf (L"Internal Error!!\n");
           reductionResult = REDUCTION_ERROR;
           return NULL;
         }

         if (newReduction == NULL) {
           reductionResult = REDUCTION_SIMPLYFIED;
         } else {
           reductionResult = REDUCTION_OK;
         }
         return newReduction;
         break;

         // This Action can never happen...
         case ACTION_GOTO:
         wprintf (L"Goto: %d", target);
         currentState = target;
         break;

         case ACTION_ACCEPT:
         reductionResult = REDUCTION_TEXT_ACCEPTED;
         if (DEBUG) wprintf (L"text parsed succesfully\n");
         return NULL;
         break;
       }
     }

   }
   reductionResult = REDUCTION_ERROR;
   return NULL;
 }


 /*!
    Computes an Action object for the input parameters

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

 wchar_t *LALR::getPossibleTokens (integer index) {
   wchar_t *resStr = new wchar_t [2560];
   resStr[0] = 0;
   for (integer i=0; i < stateTable->states[index].actions.size(); i++) {
     integer j = stateTable->states[index].actions[i].symbolIndex;
     if (symbolTable->symbols[j].kind
     == SYMBOL_TERMINAL) {
       wcscat (resStr, symbolTable->symbols[j].name);
       wcscat (resStr, L" ");
     }
   }
   wcscat (resStr, L"\n");
   return resStr;
 }

 /*!
   Builds a parse tree with reductions as nodes.
   Sets the Error object with the possible compiling errors.

  /sa getError(), getNextReduction()
 */
 Reduction *LALR::buildParseTree (bool trimReductions, bool reportOnlyOneError) {
   Reduction *reduction;
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
/*
   // Clean the stack
   for (integer i=0; i < tokenStack.size(); i++) {
	  delete tokenStack.top();
	  tokenStack.pop();
   }
*/

   if (getResult() == REDUCTION_TEXT_ACCEPTED) {
      return prevReduction;
   } else {
      return NULL;
   }
 }


 int LALR::getResult () {
     return reductionResult;
 }


 Error *LALR::getError() {
     return error;
 }


 void LALR::printReductionTree (Reduction *reduction, int deep) {
   // print tabs
 integer i;

 for (i=0; i < deep; i++) {
   wprintf (L" ");
 }

 if (reduction == NULL) {
   wprintf (L"NULL\n");
   return;
 }

 // print this node
 wprintf (symbolTable->symbols[reduction->tok->symbolIndex].name);
 wprintf (L"\n");
 for (i=0; i < reduction->childs.size(); i++) {
   if (reduction->childs[i]->kind == SYMBOL_NON_TERMINAL) {
     printReductionTree (reduction->childs[i]->reduction, deep+1);
   } else {
     for (int j=0; j < deep+1; j++) {
       wprintf (L" ");
     }
     wprintf (reduction->childs[i]->symbol);
     wprintf (L":");
     wprintf (reduction->childs[i]->image);
     wprintf (L"\n");
   }
 }
}




