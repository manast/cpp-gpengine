/***************************************************************************
                          SymbolTable.h  -  description
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
 #ifndef SYMBOLTABLE_H
 #define SYMBOLTABLE_H

 #include "misc.h"
 #include <wchar.h>


 enum SymbolType {TERMINAL = 1, NON_TERMINAL = 0};


 typedef struct SymbolStruct {
   wchar_t *name;
   SymbolType kind;
 } SymbolStruct;


 class SymbolTable {
   public:
   integer nbrEntries;
   SymbolStruct *symbols;

   SymbolTable (integer nbrEntries);
   ~SymbolTable ();

 };


 #endif

