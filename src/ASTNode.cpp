/***************************************************************************
                          ASTNode.cpp
    Base class for all the nodes in the AST.                       
                          -------------------
    begin                : Tue Jun 25 09:52:11 CEST 2002
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


 #include "ASTNode.h"
 #include "Terminal.h"


 ASTNode::~ASTNode () {
	for (unsigned int i = 0; i < children.size (); i++) {
		delete children[i];
	}
 }

 
 void ASTNode::init (const Symbol *s, ASTNode *parent) {
 	m_line = s->line;
	m_col = s->col;
    
	if (s->type == NON_TERMINAL) {
		m_image = s->symbol;
	} else {
		m_image = ((Terminal*) s)->image;
	}
    m_symbol = s->symbol;
	m_parent = parent;
 }

 void ASTNode::setImage (wstring image) {
    m_image = image;
 }

 void ASTNode::setSymbol (wstring symbol) {
    m_symbol = symbol;
 }

 wstring ASTNode::getImage () {
    return m_image;
 }

 wstring ASTNode::getSymbol () {
    return m_symbol;
 }

 void ASTNode::addChild (ASTNode *child) {
	children.push_back (child);
 }


 vector <ASTNode*> *ASTNode::getChildren () {
	return &children;
 }


 ASTNode *ASTNode::getParent () {
	return m_parent;
 }


 /*!
	Sets the parent for this node.

  /sa getParent()
  */

 void ASTNode::setParent (ASTNode *parent) {
	m_parent = parent;
 }


 void ASTNode::print (int tabs) {
	integer i,j;
	for (i=0; i < tabs; i++) {
		wprintf (L" ");
	}

	wprintf (m_symbol.c_str());
	wprintf (L":");
	wprintf (m_image.c_str());
	wprintf (L"\n");
	
	for (i=0; i < children.size(); i++) {
		if (children[i] != NULL) {
			children[i]->print (tabs+1);
		} else {
			for (j=0; j < tabs+1; j++) {
				wprintf (L" ");
			}
			wprintf(L"NULL\n");
		}
	}
 }


 



