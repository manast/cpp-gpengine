/***************************************************************************
                          Error.h  -  handles the errors
                          ------------------------------
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
 #ifndef _GP_ERROR_H
 #define _GP_ERROR_H

 #include <vector>
 #include "misc.h"
 #include "Terminal.h"

 using namespace std;

 
 #if defined (WIN32) && defined (_USRDLL)
    class __declspec(dllexport) ErrorTable;
 //   class __declspec(dllexport) vector <GPError*>; 
 #endif 


 typedef enum error_type {
     ERROR_PARSE, 
     ERROR_SCAN
 } error_type;

 typedef enum error_value {
     END_COMMENT_NOT_FOUND, // end of comment not found
     UNKNOWN_TOKEN,
     UNEXPECTED_TOKEN
 } error_value;


 class GPError  {
 public:
     error_type type;
     error_value value;
  
     Symbol *reduction;
     integer line;
     integer col;
     vector <wstring> expected;
     vector <Symbol*>  traceback;
     Terminal lastTerminal;
 };

 class ErrorTable {
   public:
   vector <GPError*>  errors;

   ErrorTable ();
   ~ErrorTable ();
   void addError (error_type type, error_value value , Symbol *rdc, 
                  Terminal *lastTerminal, vector <wstring> expected, 
                  vector <Symbol*> traceback, integer line, integer col);

   void addError (error_type type, error_value value, Symbol *rdc, 
                  integer line, integer col);
   void clear ();

   void print ();
   // void print (const ErrorReporter &reporter);

 };

 #endif

