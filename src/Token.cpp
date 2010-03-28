/***************************************************************************
                          Token.cpp  -  A simple token class
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
 #include "Token.h"

 Token::Token () {
   symbolIndex = 0;

   state = 0;
   kind = 0;
 }

 Token::~Token () {
  
 }

 Token *Token::newInstance() {
	Token *newToken = new Token ();

	newToken->symbol = symbol;
    newToken->image = image;

	newToken->col = col;
	newToken->kind = kind;
	newToken->line = line;
	newToken->state = state;
	newToken->symbolIndex = symbolIndex;

	return newToken;
 }

