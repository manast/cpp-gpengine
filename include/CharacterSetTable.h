/***************************************************************************
                          CharacterSetTable.h  -  description
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

 #ifndef _GP_CHARACTER_SET_TABLE_H
 #define _GP_CHARACTER_SET_TABLE_H

 #include "wchar.h"
 #include "misc.h"

 

 class CharacterSetTable {
   public:
   integer nbrEntries;
   wchar_t **characters;

   CharacterSetTable (integer nbrEntries);
   ~CharacterSetTable ();

 };


 #endif


















