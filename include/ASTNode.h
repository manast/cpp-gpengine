/***************************************************************************
                          ASTNode.h
                          
                             -------------------
    begin                : Tue Jun 25 09:50:11 CEST 2002
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



 #ifndef AST_NODE_H
 #define AST_NODE_H

 #include <vector>
 #include <string>
 #include <wchar.h>
 
 #include "Symbol.h"

 using namespace std;

 #if defined (WIN32) && defined (_USRDLL)
    class __declspec(dllexport) ASTNode;
 #else 
	class ASTNode;
 #endif

 
 class ASTNode {
 protected:
    std::wstring  m_symbol;
    std::wstring  m_image;

    ASTNode *m_parent;
	unsigned short m_line, m_col;
	
	std::vector <ASTNode*> children;
	
 public:
	virtual ~ASTNode ();

	void    init      (const Symbol *s, ASTNode *parent);

	void    setImage  (wstring image);
    void    setSymbol (wstring symbol);

    std::wstring getImage  ();
    std::wstring getSymbol ();
	
    void	setParent (ASTNode *parent);

	ASTNode *getParent ();

	void	addChild  (ASTNode *child);
	std::vector <ASTNode*> *getChildren ();

	void print (int tabs);
 };


#endif

