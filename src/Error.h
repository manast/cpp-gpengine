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
 #include "Reduction.h"

 using namespace std;

 typedef enum error_codes {ERROR_PARSE, ERROR_SCAN};

 typedef struct ErrorStruct  {
      ErrorStruct() { msg = NULL; }
     ~ErrorStruct() { delete [] msg; }
     int code;
     wchar_t *msg;
     Reduction *reduction;
     integer line;
     integer col;
 } ErrorStruct;

  
 class Error {
   public:
   vector <ErrorStruct*>  errors;

   Error ();
   ~Error ();
   void addError (error_codes code, wchar_t *msg, Reduction *rdc, integer line, integer col);
   void clear ();

   void print ();

 };

 #endif

