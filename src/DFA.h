/***************************************************************************
                          DFA.h  -  description
                             -------------------
    begin                : Sun Jun 2 2002
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
 #ifndef DFA_H
 #define DFA_H

 #include <stdlib.h>
 #include <vector>

 #include "misc.h"
 #include "DFAStateTable.h"
 #include "SymbolTable.h"
 #include "CharacterSetTable.h"
 #include "Token.h"
 #include "Error.h"

 #include <wctype.h>


 using namespace std;


 class DFA {
   private:
   const DFAStateTable *stateTable;
   const SymbolTable *symbolTable;
   const CharacterSetTable *characterSetTable;
   integer startState;
   bool caseSensitive;

   vector<Token*> tokens;

   Error *error;

   public:
   DFA (const DFAStateTable *stateTable, const SymbolTable *symbolTable,
   const CharacterSetTable *characterSetTable, integer startState, bool caseSensitive);
   ~DFA ();


   bool scan (wchar_t *text);
   bool scan (char *text);

   vector <Token*> &getTokens ();
   Error *getError();
 };


 #endif

