/***************************************************************************
                          ASTCreator.cpp
	      This class works as a framework for the 
	      creation of an abstract syntax tree specific 
	      for a grammar
                          -------------------
    begin                : Sun Jun 2 2002
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


 #include "ASTCreator.h"

// Include the header with YOUR AST node classes	

 ASTNode *ASTCreator::createTree (const Symbol &reductionTree) {
	 // If the tree is an empty terminal node return null
     return getASTNode (&reductionTree, NULL);
 }

 ASTNode *ASTCreator::getASTNode (const Symbol *reduction, ASTNode *parent) {
     
	/*!
	  This method has to be customized for YOUR Abstract Grammar.
	  Base your Abstract Grammar in the Context Free Grammar.
	  Check for nodes that are equivalent in both grammars and convert
	  the nodes that are not equivalent.
	 */

   
	 //vector <ASTNode*> *children= NULL;
	 wstring sym = reduction->symbol;

	 deque <Symbol*> rdcChildren;
	 if (reduction->type == NON_TERMINAL) {
		rdcChildren = ((NonTerminal*) reduction)->children;
	 } 

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

	 if ( sym == L"Start" ) {
		Start *start = new Start ();
        start->init (reduction, parent);

		start->addChild (getASTNode(rdcChildren[1], start));
		start->addChild (getASTNode(rdcChildren[3], start));
		start->addChild (getASTNode(rdcChildren[5], start));
		return start;
	 }

	 // (Example of a List)
	 ////////////////////////

	// Original Rule: 
	<StatementList> ::= <Statement> ';' <StatementList> 
                    |
	// Translated to:
	<StatementList> ::= <Statement>*

	 if (sym == L"StatementList") {
		StatementList *statementList = new StatementList ();
        statementList->init (reduction, parent);
		
		if (rdcChildren.size() == 3) {
			statementList->addChild (getASTNode (rdcChildren[0], stmtList));
			
			children = stmtList->getChildren();
			getASTNodeList (children, rdcChildren[2]->reduction, 1, 3, stmtList); 
		}
	
		return stmtList;
	 }
*/
	 /*
        If the symbol constants are included it is possible to do it in the possible way: 


            // <If Statement> ::= if <Expression> then <StatementList> end
            if (sym == RULE_IF_THEN_END_STATEMENT) {
                IfStatement *ifStatement = new IfStatement ();
                ifStatement->init (reduction, parent);
                    
                ifStmt->addChild (getASTNode(rdcChildren[1], ifStmt));
                ifStmt->addChild (getASTNode(rdcChildren[3], ifStmt));
	
                return ifStmt;
            }

            // <If Statement> ::= if <Expression> then <StatementList> else <StatementList> end
            if ( sym == RULE_IF_THEN_END_ELSE_STATEMENT) {
                IfStatement *ifStatement = new IfStatement ();
                ifStatement->init (reduction, parent);

                ifStmt->addChild (getASTNode(rdcChildren[1], ifStmt));
                ifStmt->addChild (getASTNode(rdcChildren[3], ifStmt));
	            ifStmt->addChild (getASTNode(rdcChildren[5], ifStmt));
                return ifStmt;
            }
           

     */

	 return searchEquivNode( rdcChildren, parent);
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
			result = getASTNode(rdcChildren[i], parent);
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
	
	 (Note that left NonTerminal and the last non-terminal in the rule are the same)
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
					    // if we have a rule that produces a
					    // terminal symbol, we only get the node for this reduction
					    if (rdcChildren[i]->type == TERMINAL) {
						    ast = getASTNode (reduction, parent);
					    } else {
						    ast = getASTNode (rdcChildren[i], parent);
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
                    ast = getASTNode (rdcChildren[i], parent);
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
									   
 /*!
	 This method is usefull to create nodes in the tree for rules that
	 have the following structure:
	 NonTerminal1 ::= NonTerminalA NonTerminalB ... NonTerminal1
	
	 (Note that left NonTerminal and the last non-terminal in the rule are the same)
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
						// if we have a rule that produces a
						// terminal symbol, we only get the node for this reduction
						if (rdcChildren[i]->type == TERMINAL) {
							ast = getASTNode (reduction,parent);
						} else {
							ast = getASTNode (rdcChildren[i],parent);
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
						    ast = getASTNode (rdcChildren[i], parent);
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
 
