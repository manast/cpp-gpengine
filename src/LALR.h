/***************************************************************************
                          LALR.h  -  LALR automata
                             -------------------
    begin                : Thu Jun 13 2002
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
 #ifndef LALR_H
 #define LALR_H

 #include <vector>
 #include <stack>
 #include "Token.h"
 #include "Reduction.h"
 #include "LALRStateTable.h"
 #include "RuleTable.h"
 #include "SymbolTable.h"
 #include "Error.h"


 #define ACTION_SHIFT 1
 #define ACTION_REDUCE 2
 #define ACTION_GOTO 3
 #define ACTION_ACCEPT 4


 #define REDUCTION_OK 0
 #define REDUCTION_ERROR 1
 #define REDUCTION_TEXT_ACCEPTED 2
 #define REDUCTION_SIMPLYFIED 3


 #define DEBUG false

 class LALR {
   private:

   const LALRStateTable *stateTable;
   const RuleTable *ruleTable;
   const SymbolTable *symbolTable;

   integer startState;
   integer currentState;

   integer currentLine, currentCol;

   integer tokenIndex;

   vector<Token*> tokens;
   vector<Token*> tokensList; // we save a copy of all the new tokens that we create in the
						     // parser in order to free them at the end
   stack <Token*, vector<Token*> > tokenStack;

   Reduction *currentReduction;
   Reduction *startReduction;

   Reduction *oldReduction;
   vector <Reduction*> reductionsList; // we save the reductions in order to remove them later.

   int reductionResult;

   Error *error;

   public:
   LALR (const LALRStateTable *stateTable, const SymbolTable *symbolTable,
   const RuleTable *ruleTable, integer startState);
   ~LALR ();

   /*!
     setup the parsing engine.
   */
   void parse (const vector <Token*> &tokens);

   Reduction *nextReduction (bool trimReduction, bool reportOnlyOneError);


   /*!
     Gets the result constant for the last reduction attempt.
   */
   int getResult();

   /*!
     builds a parse tree with Reductions as nodes.
     This tree is supposed to be the input to some abstract tree creator.
     Every Reduction node has a list of tokens, and every token a pointer to
     its correspondent reduction node.
   */
   Reduction *buildParseTree (bool trimReductions, bool reportOnlyOneError);


   void symplifyParseTree (Reduction *reduction);

   void printRule (integer rule);
   void printReductionTree (Reduction *reduction, int deep);

   Error *getError ();

   private:
   Action *getNextAction (integer symbolIndex, integer index);

   wchar_t *getPossibleTokens (integer index);

   void deleteReductionTree ();

 };

 #endif

