/***************************************************************************
								test.cpp  
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
 
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
 
#include <iostream>
#include <stdlib.h>

#include "CGTFile.h"
#include "ErrorReporter.h"
#include "testErrorRep.h"


void printTokens (vector <Token*> &t);

int main(int argc, char *argv[])
{
  CGTFile    cgtFile;
  char       *srcCode;
  FILE		 *file;
  Symbol     *rdc;

  ErrorTable *myErrors;
  testErrorRep myReporter;
  
  // Load source code to compile
  file =  fopen ("test1.gs", "rb");
  if (file == NULL) {
	  wprintf (L"error loading source file\n");
      return -1;
  }

  fseek (file, 0, SEEK_END);
  int fsize = ftell(file);
  fseek (file, 0, SEEK_SET);

  srcCode = new char[fsize+1];
  fread (srcCode, 1, fsize, file);
  srcCode[fsize] = 0;

  fclose (file);
        
  if (cgtFile.load ("gscript.cgt")) {
    wprintf (L"%s\n", "Grammar loaded succesfully");
    cgtFile.printInfo ();
  } else {
    wprintf (L"%s\n", "error loading file");
	return -1;
  }

  DFA *dfa = cgtFile.getScanner();

  dfa->scan(srcCode);
  myErrors = dfa->getErrors();
  myErrors->print();
  
  for (int i=0; i < myErrors->errors.size(); i++) {
    cout << myReporter.composeErrorMsg (*myErrors->errors[i]) << endl;
  }
  
  if (myErrors->errors.size() == 0) {
 
    vector <Token*> tokens = dfa->getTokens();

    printTokens (tokens);

    LALR *lalr = cgtFile.getParser();

    lalr->parse(tokens);
   
    rdc = lalr->buildParseTree(true, true);
   
    myErrors = lalr->getErrors(); 
    if (myErrors->errors.size() == 0) {
      lalr->printReductionTree(rdc, 0);
    } else {
      for (int i=0; i < myErrors->errors.size(); i++) {
        cout << myReporter.composeErrorMsg (*myErrors->errors[i]) << endl;
      }
      myErrors->print();
    }
  } else { 
      wprintf (L"Compilation Failed\n");
  }
 

  delete [] srcCode;
  delete rdc;

  return EXIT_SUCCESS;
}

   
void printTokens (vector <Token*> &t) {
  for (integer i = 0; i < t.size(); i++) {
   wchar_t *pwe = t[i]->symbol;	
    wprintf (t[i]->symbol);
    wprintf (L":");
    wprintf (t[i]->image);
    wprintf (L"\n");
  }
}






