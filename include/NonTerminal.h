/***************************************************************************
                          NonTerminal.h
 
   Baseclass for the non-terminals of the reduction tree
                          -------------------
    begin                : Fri Oct 24 2003
    copyright            : (C) 2002-2003 Manuel Astudillo
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

#ifndef _GP_NON_TERMINAL_H
#define _GP_NON_TERMINAL_H

#include <deque>
using namespace std;

#include "Symbol.h"

struct NonTerminal : public Symbol {
    NonTerminal  ();
    ~NonTerminal ();

    deque <Symbol*> children;
};

#endif

