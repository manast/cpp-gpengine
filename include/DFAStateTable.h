/***************************************************************************
                          DFAStateTable.h  -  description
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
 #ifndef _GP_DFASTATETABLE_H
 #define _GP_DFASTATETABLE_H

 #include <vector>
 #include "misc.h"

 using namespace std;

 typedef struct Edge {
   integer characterSetIndex;
   integer targetIndex;
 } Edge;

 typedef struct DFAState {
   bool accept;
   integer acceptIndex;
   vector<Edge> edges;
 } DFAState;

 class DFAStateTable {
   public:
   integer nbrEntries;
   DFAState *states;

   DFAStateTable (integer nbrEntries);
   ~DFAStateTable ();

 };

 #endif

