/***************************************************************************
                          SymbolTable.cpp  -  description
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

 #include "SymbolTable.h"



 SymbolTable::SymbolTable (integer nbrEntries) {
     this->nbrEntries = nbrEntries;
     symbols = new SymbolStruct [nbrEntries];
 }


 SymbolTable::~SymbolTable () {
   for (unsigned short i=0; i < nbrEntries; i++) {
     delete [] symbols[i].name;
   }
   delete [] symbols;
 }

