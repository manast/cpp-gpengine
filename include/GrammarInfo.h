/***************************************************************************
                          GrammarInfo.h
                          -------------------
    begin                : Sat Jun 1 2002
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

#ifndef GRAMMAR_INFO_H
#define GRAMMAR_INFO_H

#include <string>



class GrammarInfo {

public:
    std::wstring    name;
    std::wstring    version;
    std::wstring    author;
    std::wstring    about;

	GrammarInfo ();
	~GrammarInfo ();
};

#endif

