/***************************************************************************
                          CGTFile.cpp  -
                          Encapsulates the Compiled Grammar Table File
                          read operations and structures.
                             -------------------
    begin                : Fri May 31 00:53:11 CEST 2002
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

 #include "CGTFile.h"
 #include "GrammarInfo.h"


 CGTFile::CGTFile () {

   gInfo = NULL;

   errorString = NULL;

   header = NULL;

   ruleTable = NULL;
   symbolTable = NULL;
   stateTable = NULL;
   LALRTable = NULL;
   characterSetTable = NULL;

   theDFA = NULL;
   theLALR = NULL;
 }

 CGTFile::~CGTFile () {

	 delete gInfo;

	 delete [] errorString;
     delete [] header;

     // Delete tables
     delete symbolTable;
     delete stateTable;
     delete LALRTable;
     delete ruleTable;
     delete characterSetTable;

	 delete theDFA;
	 delete theLALR;
 }

 bool CGTFile::load (char *filename) {
    ifstream cgtStream;

    cgtStream.open (filename, ifstream::in | ifstream::binary);

    if (cgtStream.bad()) {
        return false;
    }

    bool result = load (&cgtStream);
    cgtStream.close();
    return result;
 }

 bool CGTFile::load (ifstream *myStream) {
   int i;	

   EntryStruct entry;

   theStream = myStream;

   // Read Header
   //////////////
   header = readUnicodeString();

   // Read Records
   ////////////////
   unsigned char recordType;
   integer nbrEntries;
   integer index;

   while (!theStream->eof()) {
     // Read record type & number of entries
     theStream->read ((char*)&recordType, sizeof (unsigned char));
     if (theStream->fail()) {
        if (theStream->eof()) {
			break;
        } else {
			return false;
        }
     }

     theStream->read ((char*) &nbrEntries, sizeof(integer));
  //  wprintf (L"Record Type: %d\n", recordType);
  //  wprintf (L"Entries: %d\n", nbrEntries);

     if (recordType != 77) {
       errorString = "Record type is not supported\n";
       return false;
     }

     // Read the type of content
     byte contentType;
     readEntry (&entry);
     contentType = entry.vByte;

   //  wprintf (L"Content Type: %d\n", contentType);

     switch (contentType) {

       // Parameters Record	
       case 'P':
	   delete gInfo;
	   gInfo = new GrammarInfo ();

       // read name
       readEntry (&entry);
       gInfo->name = entry.vString;

       // read version
       readEntry (&entry);
       gInfo->version = entry.vString;

       // read Author
       readEntry (&entry);
       gInfo->author = entry.vString;

       // read About
       readEntry (&entry);
       gInfo->about = entry.vString;

       // Case
       readEntry (&entry);
       caseSensitive = entry.vBool;

       // start symbol
       readEntry  (&entry);
       startSymbol = entry.vInteger;

       break;

       // Table Counts
       case 'T' :
       readEntry (&entry);
       nbrSymbolTable = entry.vInteger;

       // Delete & Create a Symbol Table
       delete symbolTable;
       symbolTable = new SymbolTable (nbrSymbolTable);

       readEntry (&entry);
       nbrCharacterSets = entry.vInteger;

       // Delete & Create a Character Sets Table
       delete characterSetTable;
       characterSetTable = new CharacterSetTable (nbrCharacterSets);

       // Delete & Create a Rule Table
       readEntry (&entry);
       nbrRuleTable = entry.vInteger;
       delete ruleTable;
       ruleTable = new RuleTable (nbrRuleTable);

       // Delete & Create a DFAStateTable
       readEntry (&entry);
       nbrDFATable = entry.vInteger;
       delete stateTable;
       stateTable = new DFAStateTable (nbrDFATable);

        // Delete & Create a LALR Table
       readEntry (&entry);
       nbrLALRTable = entry.vInteger;
       delete LALRTable;
       LALRTable = new LALRStateTable (nbrLALRTable);

       break;

       // Character Set Table Entry
       case 'C' :
       readEntry (&entry);
       index = entry.vInteger;

       readEntry (&entry);
       characterSetTable->characters[index] =  entry.vString;
       break;

       // Symbol Table Entry
       case 'S' :
       readEntry (&entry);
       index = entry.vInteger;

       readEntry (&entry);
       symbolTable->symbols[index].name = entry.vString;

       readEntry (&entry);
       symbolTable->symbols[index].kind = entry.vInteger;
       break;

       // Rule
       case 'R' :
       readEntry (&entry);
       index = entry.vInteger;

       readEntry (&entry);
       ruleTable->rules[index].nonTerminal = entry.vInteger;

       // Read empty field
       readEntry (&entry);

       // Read symbols for this rule (nonTerminal -> symbol0 symbol1 ... symboln)
       for (i=0; i < nbrEntries-4; i++) {
         readEntry (&entry);
        // ruleTable->rules[index].symbols.push_back (entry.vInteger);
		 RuleStruct *rst = &ruleTable->rules[index];
		 
		 vector <integer> *s = &rst->symbols;
		 s->push_back (entry.vInteger);
       }
       break;

       // Initial States
       case 'I' :
       readEntry(&entry);
       DFAInit = entry.vInteger;

       readEntry (&entry);
       LALRInit = entry.vInteger;
       break;


       // DFA State Entry
       case 'D':
       readEntry (&entry);
       index = entry.vInteger;

       // create a new State an insert it in the table
       readEntry (&entry);
       stateTable->states[index].accept = entry.vBool;

       readEntry(&entry);
       stateTable->states[index].acceptIndex = entry.vInteger;

       readEntry(&entry);

       Edge edge;
       for (i=0; i < nbrEntries-5; i+=3) {

         readEntry(&entry);
         edge.characterSetIndex = entry.vInteger;

         readEntry(&entry);
         edge.targetIndex = entry.vInteger;

         readEntry(&entry);

         stateTable->states[index].edges.push_back(edge);
       }
       break;

       // LALR State entry
       case 'L':
       readEntry(&entry);
       index = entry.vInteger;

       readEntry(&entry);

       Action action;
       for (i=0; i < nbrEntries-3; i+=4) {
         readEntry(&entry);
         action.symbolIndex = entry.vInteger;

         readEntry(&entry);
         action.action = entry.vInteger;

         readEntry(&entry);
         action.target = entry.vInteger;

         readEntry(&entry);

         LALRTable->states[index].actions.push_back(action);
       }

      break;

     }

   }
   return true;
 }

   /*
   Reads an entry in a record
   */
   void CGTFile::readEntry (EntryStruct *entry) {

     char tmpChar;
     char dataType;

     theStream->get (dataType);
     if (theStream->fail()) {
		 wprintf (L"Error reading entry\n");
	 } else {
		 switch (dataType) {
		case 'E': break;
		case 'B':
		theStream->get (tmpChar);
        if (tmpChar) {
		  entry->vBool = true;
		} else {
		  entry->vBool = false;
		}
		break;
		case 'b':
		theStream->read ((char*) &entry->vByte, sizeof(byte));
        break;
		case 'I':
		theStream->read ((char*) &entry->vInteger, sizeof(integer));
        break;
		case 'S':
		entry->vString = readUnicodeString();
		break;
     }
	}

   }


 /*
 Reads a Unicode String
 */

 wchar_t *CGTFile::readUnicodeString () {
   int i = 0;
   wchar_t readChar;
   wchar_t tmpString[512];
   wchar_t *retString;
   char   tmpChar1, tmpChar2;

   theStream->get (tmpChar1);
   theStream->get (tmpChar2);

   while ((tmpChar1 != 0) || (tmpChar2 != 0)) {
     readChar = (wchar_t) tmpChar2;
     readChar <<= 8;
     readChar |= tmpChar1;

     tmpString[i] = readChar;

     theStream->get (tmpChar1);
     theStream->get (tmpChar2);

     i++;
   }
   tmpString[i] = 0;

   retString = new wchar_t [wcslen (tmpString) + 1];

   wcscpy (retString, tmpString);

   return retString;
 }


 GrammarInfo *CGTFile::getInfo () {
	return gInfo;
 }

 DFA *CGTFile::getScanner () {
     delete theDFA;
	 theDFA = new DFA (stateTable, symbolTable,
     characterSetTable, DFAInit, caseSensitive);
     return theDFA;
 }


 LALR *CGTFile::getParser () {
	 delete theLALR;
     theLALR = new LALR (LALRTable, symbolTable, ruleTable, LALRInit);
     return theLALR;
 }

