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
 #ifndef _GP_DFA_H
 #define _GP_DFA_H

 #include <stdlib.h>
 #include <vector>
 #include <wctype.h>

 #include "misc.h"
 #include "DFAStateTable.h"
 #include "SymbolTable.h"
 #include "CharacterSetTable.h"
 #include "Token.h"
 #include "ErrorTable.h"

 using namespace std;

 #if defined (WIN32) && defined (_USRDLL)
    class __declspec(dllexport) DFA;
 #endif

 class DFA {
 public:
   DFA (const DFAStateTable *stateTable, const SymbolTable *symbolTable,
        const CharacterSetTable *characterSetTable, 
        integer startState, bool caseSensitive);
   
   ~DFA ();

   bool scan (wchar_t *text);
   bool scan (char *text);

   vector <Token*> &getTokens ();

   ErrorTable *getErrors();
 
 private:
   const DFAStateTable *stateTable;
   const SymbolTable *symbolTable;
   const CharacterSetTable *characterSetTable;
   integer startState;
   bool caseSensitive;

   vector<Token*> tokens;

   ErrorTable *errorTab;
 };


 #endif

