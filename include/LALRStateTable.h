/***************************************************************************
                          LALRStateTable.h  -  description
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
 #ifndef LALR_STATE_TABLE_H
 #define LALR_STATE_TABLE_H

 #include <vector>
 #include "misc.h"

 using namespace std;

 typedef struct Action {
   integer symbolIndex;
   integer action;
   integer target;

 } Action;

 typedef struct LALRState {
   vector<Action> actions;
 } LALRState;


 class LALRStateTable {
 public:
   integer nbrEntries;
   LALRState *states;

   LALRStateTable (integer nbrEntries);
   ~LALRStateTable ();

 };

 #endif

