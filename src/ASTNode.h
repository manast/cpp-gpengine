/***************************************************************************
                          ASTNode.h
                          
                             -------------------
    begin                : Tue Jun 25 09:50:11 CEST 2002
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



 #ifndef AST_NODE_H
 #define AST_NODE_H

 #include "Token.h"

 #include <vector>
 #include "wchar.h"

 using namespace std;

 class ASTNode;

 class ASTNode {
 protected:
	wchar_t *name;

	unsigned short line, col;
	wchar_t *image;

	vector <ASTNode*> children;
	ASTNode *parent;

 public:
    ASTNode ();
	virtual ~ASTNode ();

	void init (Token *t);
	void	setParent (ASTNode *parent);
	ASTNode *getParent ();
	vector <ASTNode*> *getChildren ();

	void toString (int tabs);
 };


#endif