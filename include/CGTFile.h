/***************************************************************************
                          CGTFile.h  -
                          Encapsulates the Compiled Grammar Table File
                          read operations and structures.
                             -------------------
    begin                : Sat Jun 1 2002
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
 #ifndef _GP_CGTFILE_H
 #define _GP_CGTFILE_H

 #include <stdio.h>
 #include <wchar.h>
 #include <iostream> 
 #include <fstream>
 #include <vector>

 #include "misc.h"
 #include "DFA.h"
 #include "LALR.h"
 #include "SymbolTable.h" 
 #include "GrammarInfo.h"

 using namespace std;

 typedef union EntryStruct {
   bool vBool;
   integer vInteger;
   byte vByte;
   wchar_t *vString;
 } EntryStruct ;

 #if defined (WIN32) && defined (_USRDLL)
    class __declspec(dllexport) CGTFile;
 #endif

 class CGTFile {

 public:

   CGTFile ();
   ~CGTFile ();

    /*
   Loads a CGT File.
   Returns true if succesfull, false if error.
   */
   bool load (char *filename);
   bool load (ifstream *myStream);

   GrammarInfo *getInfo ();	

   DFA *getScanner ();

   LALR *getParser ();

   char *getError ();

   void printInfo ();

 private:

   void readEntry (EntryStruct *entry);
   wchar_t *readUnicodeString ();
   // Header
   wchar_t *header;

   // Info
   GrammarInfo *gInfo;
   bool caseSensitive;
   integer startSymbol;

   char *errorString;

  // FILE *file;
   ifstream *theStream;

   // Character Table
   integer nbrCharacterSets;
   CharacterSetTable *characterSetTable;

   // Symbol Table
   integer nbrSymbolTable;
   SymbolTable *symbolTable;

   // DFA Table
   integer nbrDFATable;
   DFAStateTable *stateTable;

   // Rules Table
   integer nbrRuleTable;
   RuleTable *ruleTable;

   // LALR Table
   integer nbrLALRTable;
   LALRStateTable *LALRTable;

   // Init States
   integer DFAInit;
   integer LALRInit;

   DFA *theDFA;
   LALR *theLALR;

 };

 #endif

