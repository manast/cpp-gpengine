/***************************************************************************
								logic.cpp  
    This example tries to show how the ASTCreator framework can be used 
    to convert the Reduction tree to an Abstract Syntax Tree.
                             -------------------
    begin                : Fri May 31 00:53:11 CEST 2002
    copyright            : (C) 2002-2003 by Manuel Astudillo
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
 
#include <iostream>
#include <stdlib.h>

#include "CGTFile.h"
#include "simpleErrorRep.h"
#include "LogicASTCreator.h"


char *load_source (char *filename);
void printTokens (vector <Token*> &t);
   
int main(int argc, char *argv[])
{
  CGTFile    cgtFile;
  char       *source;
  Symbol     *rdc;
  DFA        *dfa;
  LALR       *lalr;

  ErrorTable       *myErrors;
  ErrorReporter    myReporter;
  LogicASTCreator  myASTCreator;

  // Load grammar file
  if (cgtFile.load ("logic.cgt")) {
    wprintf (L"%s\n", "Grammar loaded succesfully");
    cgtFile.printInfo ();
  } else {
    wprintf (L"%s\n", "error loading file");
	return -1;
  }

  // Load source file
  char *filename = "test.logic";
  source = load_source (filename);
  if (source == NULL) {
      wprintf (L"Error loading source file\n");
      return -1;
  }

  // Get DFA (Deterministic Finite Automata) from the cgt file
  dfa = cgtFile.getScanner();

  // Scan the source in search of tokens
  dfa->scan(source);
  
  delete [] source;
 
  // Get the error table
  myErrors = dfa->getErrors();
  
  // If there are errors report them
  if (myErrors->errors.size() > 0) {
    for (int i=0; i < myErrors->errors.size(); i++) {
        cout << filename << ":";
        cout << myReporter.composeErrorMsg (*myErrors->errors[i]) << endl;
    }
    return -1;
  }
 
  // Get the tokens to feed the LALR machine with them
  vector <Token*> tokens = dfa->getTokens();
  //printTokens (tokens);

  // Get the LALR (Look Ahead, Left-to-right parse, Rightmost-derivation)
  lalr = cgtFile.getParser();
  
  // Parse the tokens
  rdc = lalr->parse (tokens, true, true);
   
  myErrors = lalr->getErrors(); 
  if (myErrors->errors.size() != 0) {
    for (int i=0; i < myErrors->errors.size(); i++) {
        cout << filename << ":";
        cout << myReporter.composeErrorMsg (*myErrors->errors[i]) << endl;
    }
    return -1;
  }
  ASTNode *start = myASTCreator.createTree (*rdc);
  start->print (0);
  
  //lalr->printReductionTree(rdc, 0);

  delete rdc;

  return EXIT_SUCCESS;
}

   
void printTokens (vector <Token*> &t) {
  for (integer i = 0; i < t.size(); i++) {	
    wprintf (t[i]->symbol.c_str());
    wprintf (L":");
    wprintf (t[i]->image.c_str());
    wprintf (L"\n");
  }
}

char *load_source (char *filename) {
  FILE *file =  fopen (filename, "rb");
  if (file == NULL) {
      return NULL;
  }

  fseek (file, 0, SEEK_END);
  int fsize = ftell(file);
  fseek (file, 0, SEEK_SET);

  char *src_code;
  src_code = new char[fsize+1];
  fread (src_code, 1, fsize, file);
  src_code[fsize] = 0;

  fclose (file);
  return src_code;
}




