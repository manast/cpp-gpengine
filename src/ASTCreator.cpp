/***************************************************************************
                          ASTCreator.cpp
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


 #include "ASTCreator.h"

// Include the header with YOUR AST node classes
// (example)  #include "ASTClasses.h"	

 ASTNode *ASTCreator::createTree (const Symbol &reductionTree) {
	 // If the tree is an empty terminal node return null
     if (reductionTree.type == TERMINAL) {
         return NULL;
     } else {
        return getASTNode ((NonTerminal*) &reductionTree, NULL);
     }
 }

 ASTNode *ASTCreator::getASTNode (const NonTerminal *reduction, ASTNode *parent) {
     
	 vector <ASTNode*> *children = NULL;

	/*!
	  This method has to be customized for YOUR Abstract Grammar.
	  Base your Abstract Grammar in the Context Free Grammar.
	  Check for nodes that are equivalent in both grammars and convert
	  the nodes that are not equivalent.

	  Here we make some assumptios:
	  1 - The reduction tree is correct. If it is not correct the behaviour of this
	  method is undefined.

	  2 - if one node in the reduction has no AST equivalent, then this node's associated
	  reduction (in case of a non terminal symbol) can only have 1 or less children which
	  have an AST equivalent node. 
	  (this is a bit tricky, but it means that if a non terminal is not relevant in the 
	  AST tree then the rules produced by this non terminal can only have at most one 
	  symbol which has an equivalent in the AST tree)

	  3 - The reductions must be trimmed. (i.e. no reductions in this form:
		nonTerminal1 ::= nonTerminal2

	 */

//	 Token *tok = reduction->tok;
	 wstring sym = reduction->symbol;
	 deque <Symbol*> rdcChildren = reduction->children;

	 /*
	 Next is a colection of if statements that checks for the
	  equivalency between nodes in the reduction tree and in the
	  desired Abstract Syntax Tree.
	  Note as we always pass the latest node as the parent for the children.
	  Having the parent is often usefull when doing the type analysis or
	  interpreting the AST.
	 */

	 /*
	// (Example of a simple rule) Check for Start node
	///////////////////////////////////////////////////

	// Original Rule:
	<Start> ::= begin <ConstList> defs <DefsList> prog <StatementList> end

	// Translated to:
	<Start> ::= <ConstList> <DefsList> <StatementList>

	 if (wcscmp (sym, L"Start") == 0) {
		Start *start = new Start ();
		start->init (tok);
		
		children = start->getChildren();

		children->push_back (getASTNode(rdcChildren[1]->reduction, start));
		children->push_back (getASTNode(rdcChildren[3]->reduction, start));
		children->push_back (getASTNode(rdcChildren[5]->reduction, start));
		return start;
	 }

	 // (Example of a List)
	 ////////////////////////

	// Original Rule: 
	<StatementList> ::= <Statement> ';' <StatementList> 
                    |
	// Translated to:
	<StatementList> ::= <Statement>*

	 if (wcscmp (sym, L"StatementList") == 0) {
		StatementList *stmtList = new StatementList ();
		stmtList->init (tok);

		children = stmtList->getChildren();

		if (rdcChildren.size() > 0) {
			ASTNode *ast = getASTNode (rdcChildren[0]->reduction, stmtList);
			if (ast != NULL) {
				children->push_back (ast);
			}
			getASTNodeList (children, rdcChildren[2]->reduction, 1, 3, stmtList); 
		}
	
		return stmtList;
	 }
*/

	 return searchEquivNode(rdcChildren, parent);
 }

/*!
 If the node has not an equivalent in the Abstract Tree we just search
 for more equivalent nodes in their children. If none found return NULL.
*/
 ASTNode *ASTCreator::searchEquivNode (const deque <Symbol*> &rdcChildren,
	 ASTNode *parent) {
 	 ASTNode *result = NULL;
	 for (unsigned short i=0; i < rdcChildren.size(); i ++) {
		 if (rdcChildren[i]->type == NON_TERMINAL) {
			result = getASTNode((NonTerminal*)rdcChildren[i], parent);
			if (result != NULL) {
				break;
			}	
		}
	 }  
	 return result;
 }
 /*!
	 This method is usefull to create nodes in the tree for rules that
	 have the following structure:
	 NonTerminal1 ::= NonTerminalA NonTerminalB ... NonTerminal1
	
	 /param children vector where the children will be added
	 /param iterNode name of the Iterative node
	 /param reduction reduction tree where the list resides
	 /param nbrInsert specifies the number of children to insert in the vector. 
	  Begining from the left of the rule.
	 /param nbrElements specifies the number of element in the "iterative" production.
	 /param parent Parent node, where the list will be hanging.
 */
 void ASTCreator::getASTNodeList (vector <ASTNode*> *children, wstring iterNode,
	              NonTerminal *reduction, int nbrInsert, int nbrElements, ASTNode *parent) {
	integer i;
	ASTNode *ast;

	wstring sym = reduction->symbol;

	deque <Symbol*> rdcChildren = reduction->children;
	if (sym == iterNode) {
		int size = rdcChildren.size();
		if (size > 0) {
			if (size < nbrElements) {
				for (i=0; i < rdcChildren.size(); i++) {
					if (i < nbrInsert) {
					// if the child reduction is NULL, we have a rule that produces a
					// terminal symbol. so we only get the node for this reduction
						if (rdcChildren[i]->type == TERMINAL) {
							ast = getASTNode (reduction,parent);
						} else {
							ast = getASTNode ((NonTerminal*)rdcChildren[i],parent);
						}
						// Do not insert NULL childs
						if (ast!=NULL) {
							children->push_back(ast);
						}
					}
				}
			} else {
				for (i=0; i < rdcChildren.size()-1; i++) {
					if (i < nbrInsert) {
						// Do not insert NULL childs
                        if (rdcChildren[i]->type == NON_TERMINAL) {
						    ast = getASTNode ((NonTerminal*)rdcChildren[i], parent);
                        } else {
                            ast = NULL;
                        }

                        if (ast!=NULL) {
							children->push_back(ast);
						}
					}	
				}
                if (rdcChildren[i]->type == NON_TERMINAL) {
				    getASTNodeList (children, iterNode, (NonTerminal*) rdcChildren[i],
                                    nbrInsert, nbrElements, parent);
                }
			}
		}

	} else {
		// If this is not the iterNode then we just push this node as a child.
		ast = getASTNode (reduction, parent);
		children->push_back(ast);
	}
}
 

	 /*!
	 This method is usefull to create nodes in the tree for rules that
	 have the following structure:
	 NonTerminal1 ::= NonTerminalA NonTerminalB ... NonTerminal1
	
	 /param children vector where the children will be added
	 /param reduction reduction tree where the list resides
	 /param nbrInsert specifies the number of children to insert in the vector. 
	  Begining from the left of the rule.
	 /param nbrElements specifies the number of element in the "iterative" production.
	 /param parent Parent node, where the list will be hanging.
 */

 void ASTCreator::getASTNodeList (vector <ASTNode*> *children, 
	 NonTerminal *reduction, int nbrInsert, int nbrElements, ASTNode *parent) {
	integer i;
	ASTNode *ast;
	deque <Symbol*> rdcChildren = reduction->children;
	
	int size = rdcChildren.size();

	if (size > 0) {
		if (size < nbrElements) {
			for (i=0; i < rdcChildren.size(); i++) {
				if (i < nbrInsert) {
					// if the child reduction is NULL, we have a rule that produces a
					// terminal symbol. so we only get the node for this reduction
					if (rdcChildren[i]->type == TERMINAL) {
						ast = getASTNode (reduction, parent);
					} else {
						ast = getASTNode ((NonTerminal*)rdcChildren[i], parent);
					}
					// Do not insert NULL childs
					if (ast!=NULL) {
						children->push_back(ast);
					}
				}
			}
		} else {
			for (i=0; i < rdcChildren.size()-1; i++) {
				if (i < nbrInsert) {
					// Do not insert NULL childs
                    if (rdcChildren[i]->type == NON_TERMINAL) {
					    ast = getASTNode ((NonTerminal*)rdcChildren[i], parent);
                    } else {
                        ast = NULL;
                    }
                    if (ast!=NULL) {
						children->push_back(ast);
					}
				}	
			}
            if (rdcChildren[i]->type == NON_TERMINAL) {
			    getASTNodeList (children, (NonTerminal*) rdcChildren[i],
			    nbrInsert, nbrElements, parent);
            }
		}
	}
}
 

