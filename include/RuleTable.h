/***************************************************************************
                          RuleTable.h  -  description
                             -------------------
    begin                : Fri Jun 14 2002
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
 #ifndef RULE_TABLE_H
 #define RULE_TABLE_H

 #include "misc.h"
 #include <vector>

 using namespace std;


 typedef struct RuleStruct {
   integer nonTerminal;
   vector<integer> symbols;
 } RuleStruct;

 class RuleTable {
   public:
   integer nbrEntries;
   RuleStruct *rules;

   RuleTable (integer nbrEntries);
   ~RuleTable ();

 };



 #endif

