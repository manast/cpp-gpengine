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
#include "Reduction.h"
#include "ASTNode.h"

using namespace std;

class ASTCreator {
	public:
		/*! 
			Creates an AST based on the reduction tree.
		*/
		ASTNode *createTree (const Reduction &reduction);

	protected:
		/*!
		  This class is the most important one. This is the one that
		  must be customized.
		  See the implementation of this method for guidelines.
		*/
		virtual ASTNode *getASTNode (const Reduction *reduction, ASTNode *parent);

		void getASTNodeList (vector <ASTNode*> *children, wchar_t *iterNode,
			Reduction *reduction, int nbrInsert, int nbrElements, ASTNode *parent);

		void getASTNodeList (vector <ASTNode*> *children, 
			Reduction *reduction, int nbrInsert, int nbrElements, ASTNode *parent);

		ASTNode *ASTCreator::searchEquivNode (const deque <Token*> &rdcChildren,
			ASTNode *parent);
};

#endif 