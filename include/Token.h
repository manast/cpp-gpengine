/***************************************************************************
                          Token.h  -  description
                             -------------------
    begin                : Sun Jun 2 2002
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
 #ifndef TOKEN_H
 #define TOKEN_H

 #include <string>
 #include "misc.h"
 

 class Token;


 class Token {
   public:
   Token ();
   ~Token();
   Token *newInstance ();

   std::wstring symbol;
   std::wstring image;
   integer symbolIndex;
   integer line, col;

   integer state;
   integer kind;
 };

 #endif

