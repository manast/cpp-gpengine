/***************************************************************************
                          Token.h  -  description
                             -------------------
    begin                : Sun Jun 2 2002
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
 #ifndef TOKEN_H
 #define TOKEN_H

 #include <wchar.h>
 #include "misc.h"
 

 class Token;


 class Token {
   public:
   Token ();
   ~Token();
   Token *newInstance ();

   wchar_t *symbol;
   wchar_t *image;
   integer symbolIndex;
   integer line, col;

   integer state;
   integer kind;
 };

 #endif

