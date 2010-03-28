/***************************************************************************
                          Error.cpp  -  description
                             -------------------
    begin                : Tue Jun 18 2002
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


  #include "ErrorTable.h"

  ErrorTable::ErrorTable () {
    errors.clear();
  }


  ErrorTable::~ErrorTable () {
    for (unsigned short i = 0; i < errors.size(); i++) {
	  delete errors[i];
    }
  }

  void ErrorTable::clear () {
    errors.clear();
  }

  void ErrorTable::addError (error_type type, error_value value, Symbol *rdc, 
                             Terminal *lastTerminal, vector <wstring> expected, 
                             vector <Symbol*> traceback, integer line, integer col) {  
     GPError *err = new GPError ();

     err->expected = expected;
     err->traceback = traceback;

     err->line = line;
     err->col = col;

     err->type = type;
     err->value = value;
     err->reduction = rdc;

     err->lastTerminal = *lastTerminal;

     errors.push_back (err);
   }

   void ErrorTable::addError (error_type type, error_value value, Symbol *rdc, 
                         integer line, integer col) {
     GPError *err = new GPError ();

     err->line = line;
     err->col = col;

     err->type = type;
     err->value = value;
     err->reduction = rdc;

     errors.push_back (err);
   }

  void ErrorTable::print () {
    unsigned int i,k;
    for (i = 0; i < errors.size(); i++) {
       wprintf (L"Error line: %d, col: %d ", errors[i]->line, errors[i]->col);
      // wprintf (errors[i]->msg);
       wprintf (L"\n");
       if (errors[i]->reduction != NULL) {
            wprintf (L"Last correct parsed token was: ");
            wprintf (errors[i]->reduction->symbol.c_str());
            wprintf (L"\n");
       }

       wprintf (L"Expected Tokens: \n");
       for (k = 0; k < errors[i]->expected.size (); k++) {
            //wchar_t *a = errors[i]->traceback[k]->symbol;
            wprintf (errors[i]->expected[k].c_str());
            wprintf (L"\n");
       }

       wprintf (L"Tokens Traceback: \n");
       for (k = 0; k < errors[i]->traceback.size (); k++) {
            //wchar_t *a = errors[i]->traceback[k]->symbol;
            //if (a != NULL) {
                wprintf (errors[i]->traceback[k]->symbol.c_str());
                wprintf (L"\n");
            //}
       }

   }
  }

