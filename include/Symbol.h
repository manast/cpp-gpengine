/***************************************************************************
                          Symbol.h
 
   Superclass for the symbols of the reduction tree
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

#ifndef _GP_SYMBOL_H
#define _GP_SYMBOL_H

#include <string>
#include "SymbolTable.h"
#include "misc.h"

using namespace std;

#if defined (WIN32) && defined (_USRDLL)
	// Windows crap!. Maybe it is possible to export this without generating 
	// any warnings... 
	struct __declspec(dllexport) Symbol;
	//class __declspec(dllexport) wstring;    
#endif


class Symbol {
public:
	Symbol ();
    virtual ~Symbol ();
    SymbolType type;
   
    Symbol *parent;
    wstring symbol;

    integer symbolIndex;
    integer state;
    integer line, col;

	bool trimmed;
};


#endif

