/***************************************************************************
                          Error.h  -  handles the errors
                             -------------------
    begin                : Mon Jun 17 2002
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
 #ifndef ERROR_H
 #define ERROR_H

 #include <vector>
 #include "misc.h"

 using namespace std;

 typedef struct ErrorStruct  {
      ErrorStruct() { msg = NULL; }
     ~ErrorStruct() { delete [] msg; }
     wchar_t *msg;
     integer line;
     integer col;
 } ErrorStruct;

  
 class Error {
   public:
   vector <ErrorStruct*>  errors;

   Error ();
   ~Error ();
   void addError (wchar_t *msg, integer line, integer col);
   void clear ();

   void print ();

 };

 #endif

