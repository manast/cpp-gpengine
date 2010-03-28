/***************************************************************************
                          Symbol.cpp
 
   Superclass for the symbols of the reduction tree
                          -------------------
    begin                : Fri Oct 24 2003
    copyright            : (C) 2002-2003 Manuel Astudillo

 ***************************************************************************/
 /***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#include "Symbol.h"

Symbol::Symbol () {
	trimmed = false;
}

Symbol::~Symbol () {
  // Empty destructor
}

