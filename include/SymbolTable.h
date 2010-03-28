/***************************************************************************
                          SymbolTable.h  -  description
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
 #ifndef SYMBOLTABLE_H
 #define SYMBOLTABLE_H

 #include "misc.h"
 #include <string>


 enum SymbolType 
{ 
	TERMINAL = 1, 
	NON_TERMINAL = 0,
	WHITESPACE = 2,
	END_SYMBOL = 3,
	START_COMMENT = 4,
	END_COMMENT = 5,
	LINE_COMMENT = 6
 };


 typedef struct SymbolStruct {
   std::wstring    name;
   SymbolType kind;
 } SymbolStruct;


 class SymbolTable {
   public:
   integer m_nbrEntries;
   SymbolStruct *symbols;

   SymbolTable (integer nbrEntries);
   ~SymbolTable ();
 };


 #endif

