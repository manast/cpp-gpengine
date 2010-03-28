/***************************************************************************
                          RuleTable.cpp  -  description
                             -------------------
    begin                : Fri Jun 14 2002
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

 #include "RuleTable.h"

 RuleTable::RuleTable (integer nbrEntries) {
   this->nbrEntries = nbrEntries;
   rules = new RuleStruct [nbrEntries];
 }

 RuleTable::~RuleTable () {
    delete [] rules;

 }

