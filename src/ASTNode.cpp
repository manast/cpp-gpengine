/***************************************************************************
                          ASTNode.cpp
    Base class for all the nodes in the AST.                       
                          -------------------
    begin                : Tue Jun 25 09:52:11 CEST 2002
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


 #include "ASTNode.h"
 #include "Terminal.h"

 ASTNode::ASTNode () {
	 image = L"";
     symbol = L"";
 } 

 ASTNode::~ASTNode () {
	for (unsigned int i = 0; i < children.size (); i++) {
		delete children[i];
	}
 }

 
 void ASTNode::init (const NonTerminal &s) {
 	line = s.line;
	col = s.col;
    
    image = s.symbol;
    symbol = s.symbol;
    
	parent = NULL;
 }

 void ASTNode::setImage (wstring image) {
    this->image = image;
 }

 void ASTNode::setSymbol (wstring symbol) {
    this->symbol = symbol;
 }

 wstring ASTNode::getImage () {
    return image;
 }

 wstring ASTNode::getSymbol () {
    return symbol;
 }




 vector <ASTNode*> *ASTNode::getChildren () {
	return &children;
 }


 ASTNode *ASTNode::getParent () {
	return parent;
 }


 /*!
	Sets the parent for this node.

  /sa getParent()
  */

 void ASTNode::setParent (ASTNode *parent) {
	this->parent = parent;
 }


 void ASTNode::toString (int tabs) {
	integer i,j;
	for (i=0; i < tabs; i++) {
		wprintf (L" ");
	}

	wprintf (image.c_str());
	wprintf (L"\n");
	
	for (i=0; i < children.size(); i++) {
		if (children[i] != NULL) {
			children[i]->toString (tabs+1);
		} else {
			for (j=0; j < tabs+1; j++) {
				wprintf (L" ");
			}
			wprintf(L"NULL\n");
		}
	}
 }


 



