/***************************************************************************
                          DFAStateTable.cpp  -  description
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

 #include "DFAStateTable.h"


 DFAStateTable::DFAStateTable (integer nbrEntries) {
     this->nbrEntries = nbrEntries;
     states = new DFAState [nbrEntries];
 }


 DFAStateTable::~DFAStateTable () {
     delete [] states;
 }

