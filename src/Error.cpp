/***************************************************************************
                          Error.cpp  -  description
                             -------------------
    begin                : Tue Jun 18 2002
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


  #include "Error.h"

  Error::Error () {
    errors.clear();
  }


  Error::~Error () {
    for (unsigned short i = 0; i < errors.size(); i++) {
      delete [] errors[i]->msg;
	  delete errors[i];
    }
  }

  void Error::clear () {
    errors.clear();
  }

   void Error::addError (wchar_t *msg, integer line, integer col) {
     ErrorStruct *err = new ErrorStruct;
     err->msg = new wchar_t [wcslen (msg)+1];

     wcscpy (err->msg, msg);

     err->line = line;
     err->col = col;

     errors.push_back (err);
   }

   void Error::print () {
     for (unsigned short i = 0; i < errors.size(); i++) {
       wprintf (L"Error line: %d, col: %d ", errors[i]->line, errors[i]->col);
       wprintf (errors[i]->msg);
       wprintf (L"\n");
     }
   }

