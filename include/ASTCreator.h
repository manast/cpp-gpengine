/***************************************************************************
                          ASTCreator.h 
						  This class works as a framework for the 
						  creation of an abstract syntax tree specific 
						  for a grammar
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

#ifndef AST_CREATOR_H
#define AST_CREATOR_H

#include <vector>
#include "NonTerminal.h"
#include "ASTNode.h"

using namespace std;

#if defined (WIN32) && defined (_USRDLL)
    class __declspec(dllexport) ASTCreator;
#endif

#ifndef CREATE_NODE
	#define CREATE_NODE(X,x) X *x = new X(); x->init(*reduction); x->setParent(parent);  
#endif

class ASTCreator {
	public:
		/*! 
			Creates an AST based on the reduction tree.
		*/
		ASTNode *createTree (const Symbol &reductionTree);

	protected:
		/*!
		  This class is the most important one. This is the one that
		  must be customized.
		  See the implementation of this method for guidelines.
		*/
		virtual ASTNode *getASTNode (const Symbol *reduction, ASTNode *parent);

		void getASTNodeList (vector <ASTNode*> *children, wstring iterNode,
			NonTerminal *reduction, int nbrInsert, int nbrElements, ASTNode *parent);

		void getASTNodeList (vector <ASTNode*> *children, 
			NonTerminal *reduction, int nbrInsert, int nbrElements, ASTNode *parent);

		ASTNode *searchEquivNode (const deque <Symbol*> &rdcChildren,
			ASTNode *parent);
};

#endif
 
