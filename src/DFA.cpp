/***************************************************************************
                          DFA.cpp  -  Deterministic Finite Automata
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


 #include "DFA.h"


 DFA::DFA (const DFAStateTable *stateTable, const SymbolTable *symbolTable,
 const CharacterSetTable *characterSetTable, integer startState, bool caseSensitive) {
   this->startState = startState;
   this->stateTable = stateTable;
   this->symbolTable = symbolTable;
   this->characterSetTable = characterSetTable;
   this->caseSensitive = caseSensitive;

   errorTab = NULL;
 }

 DFA::~DFA () {
   for (integer j = 0; j < tokens.size(); j++) {
		delete tokens[j];
   }
   
   delete errorTab;
 }


 bool DFA::scan (char *text) {
	   wchar_t *wtext = new wchar_t [strlen(text)+1];
	   mbstowcs (wtext, text, strlen(text)+1);
		
	   bool res = scan (wtext);

	   delete [] wtext;

	   return res;
 }


 bool DFA::scan (wchar_t *text) {

   bool commentBlock = false;
   bool commentLine = false;
   integer currentLine = 1, currentCol = 1, tokenBeginCol = 1;

   Token *t = NULL;
  
   wstring tmpImage;
   wchar_t *tokenSymbol, *tokenImage;
   wchar_t currentChar;
   integer currentState = startState;
   int i=0, imgIndex = 0;
   integer j;

   // Free the memory for every token that might be stored in this vector
   for (j = 0; j < tokens.size(); j++) {
		delete tokens[j];
   }	

   tokens.clear();

   delete errorTab;
   errorTab = new ErrorTable();

   bool run = true;

   while (run) {
	 if (text[i] == 0) {
         // Check if Comment Block not ended
         if (commentBlock) {
		    // Set error and return
            errorTab->addError (ERROR_SCAN, END_COMMENT_NOT_FOUND, 
                                NULL, currentLine, tokenBeginCol);
            currentState = startState;
           
            tmpImage.clear();
			return false;
         } else {
            run = false;
         }
	 }
     if (text[i] == L'\n') {
       currentLine++;
       currentCol = 1;
       if (commentLine) {
         commentLine = false;
       
         if (text[i] == 0) {
           break;
         }
       }
     }

     if (!caseSensitive) {
       currentChar = (wchar_t) towlower (text[i]);
     } else {
       currentChar = (wchar_t) text[i];
     }

     if (!commentLine) {

	   tmpImage.append (1,text[i]);

       // Check which is the next state
       integer e;
       bool changedState = false;
       for (e = 0; e < stateTable->states[currentState].edges.size(); e++) {

         integer index = stateTable->states[currentState].
         edges[e].characterSetIndex;
         // Check if the current character matchs one of the edge string
         wchar_t *edgeString = characterSetTable->characters[index];
         integer s = 0;
         while (edgeString[s] != 0) {
           if (currentChar == edgeString[s]) {
             currentState = stateTable->states[currentState].edges[e].targetIndex;
             changedState = true;
             break;
           }
           s++;
         }
         if (changedState) break;

       }

       if (!changedState) {
         
		 // Check if it is an Accept state
         if (stateTable->states[currentState].accept) {
           i--;
		   currentCol--;
           // If the current character was a \n we have to decrement the line
           // counter
           if (text[i+1] == L'\n') {
             currentLine--;
           }

           // Check for type of symbol
           integer index2 = stateTable->states[currentState].acceptIndex;
           switch (symbolTable->symbols[index2].kind) {
             // Non terminal symbol
             case 0:
             // Cannot be
             break;

             // Terminal symbol
             case 1 :
             if (!commentBlock) {
              // tmpImage[imgIndex-1] = 0;
               tokenSymbol = new wchar_t [wcslen(symbolTable->symbols[index2].name)+1];
               tokenImage = new wchar_t [tmpImage.length()+1];

               wcscpy (tokenSymbol, symbolTable->symbols[index2].name);
               wcscpy (tokenImage, tmpImage.c_str());

               t = new Token();
               t->symbol = tokenSymbol;
               t->image = tokenImage;
               t->symbolIndex = index2;
               t->kind = TERMINAL;

               t->line = currentLine;
               t->col = tokenBeginCol;

               tokens.push_back(t);
             }
			   tokenBeginCol = currentCol;
             break;

             // Whitespaces
             case 2:
             // Just dont do anything or generate error for token not accepted
				tokenBeginCol = currentCol;
             break;

             // End symbol
             case 3:
             wprintf (L"EOF SYMBOL");
             break;

             // Comment Start
             case 4:
             commentBlock = true;
             break;
             
             // Comment End
             case 5:
             commentBlock = false;
             break;

             case 6:
             commentLine = true;
             break;
           }
           currentState = startState;
       
		   tmpImage.clear();
		 } else {
           if (!commentBlock) {
             // Set error and return
             errorTab->addError (ERROR_SCAN, UNKNOWN_TOKEN, NULL, currentLine, tokenBeginCol);
             currentState = startState;
     
			 tmpImage.clear();            
			 return false;
           }
           tokenBeginCol = currentCol;
         }
       }

     }
     i++;
     currentCol++;
   }

   // Generate EOF token
   t = new Token ();
   t->symbol = new wchar_t [wcslen(L"EOF")+1];
   t->image = new wchar_t [wcslen (L"EOF")+1];
   t->line = currentLine;
   t->col = currentCol;

   wcscpy (t->symbol, L"EOF");
   wcscpy (t->image, L"EOF");
   tokens.push_back(t);

   return true;
 }

 vector <Token*> &DFA::getTokens () {
    // preliminar stuff here
    return tokens;

 }

 ErrorTable *DFA::getErrors () {
   return errorTab;
 }


