

#include "LogicASTCreator.h"
#include "logic_consts.h"
#include "ASTClasses.h"

// Please read AbstractSyntaxGrammr.txt for info on the abstract grammar

ASTNode *LogicASTCreator::getASTNode (const Symbol *reduction, 
				      ASTNode *parent) {    
  vector <ASTNode*> *children = NULL;
  int ind; 
  
  deque <Symbol*> rdcChildren;
  
  // Check for Non Terminals first
  if (reduction->type == NON_TERMINAL) {
    ind = ((NonTerminal*) reduction)->ruleIndex;
    rdcChildren = ((NonTerminal*) reduction)->children;
    
    /*
      Next is a colection of if statements that checks for the
      equivalency between nodes in the reduction tree and in the
      desired Abstract Syntax Tree.
      
      Note as we always pass the current node as the parent for the children.
      Having the parent is often usefull when doing the type analysis or
      interpreting the AST.
    */
    
    // <Start> ::= <NewLineList> <AxiomList>
    // Start := AxiomList
    if ( ind == RULE_START) {
      CREATE_NODE (Start, start);
      
      start->addChild (getASTNode(rdcChildren[1], start));
      return start;
    }
    
    // <AxiomList> ::= <Axiom> <AxiomList>
    // AxiomList := Axiom*
    if (ind == RULE_AXIOMLIST) {
      CREATE_NODE (AxiomList, axiomList);
      
      axiomList->addChild (getASTNode (rdcChildren[0], axiomList));
      
      children = axiomList->getChildren();
      getASTNodeList (children, (NonTerminal*) rdcChildren[1], 1, 2, 
		      axiomList); 
      return axiomList;
    }
    
    // <Implication> ::= <DoubleImplication> '->' <Implication>
    // Implication:Axiom := Axiom Axiom
    if (ind == RULE_IMPLICATION_MINUSGT) {
      CREATE_NODE (Implication, implication);
      
      implication->addChild (getASTNode (rdcChildren[0], implication));
      implication->addChild (getASTNode (rdcChildren[2], implication));
      return implication;
    }
    
    // <DoubleImplication> ::= <Or> '<->' <DoubleImplication>
    // DoubleImplication:Axiom := Axiom Axiom
    if (ind == RULE_DOUBLEIMPLICATION_LTMINUSGT) {
      CREATE_NODE (DoubleImplication, doubleImplication);
      
      doubleImplication->addChild (getASTNode (rdcChildren[0], 
					       doubleImplication));
      doubleImplication->addChild (getASTNode (rdcChildren[2], 
					       doubleImplication));
      return doubleImplication;
    }
    
    // <Or> ::= <And> OR <Or>
    // Or:Axiom := Axiom Axiom
    if (ind == RULE_OR_OR) {
      CREATE_NODE (Or, or);
      
      or->addChild (getASTNode (rdcChildren[0], or));
      or->addChild (getASTNode (rdcChildren[2], or));
      return or;
    }
    
    // <And> ::= <Not> AND <And>
    // And:Axiom := Axiom Axiom
    if (ind == RULE_AND_AND) {
      CREATE_NODE (And, and);
      
      and->addChild (getASTNode (rdcChildren[0], and));
      and->addChild (getASTNode (rdcChildren[2], and));
      return and;
    }
    
    // <Not> ::= NOT <Value> 
    // Not:Axiom := Axiom
    if (ind == RULE_NOT_NOT) {
      CREATE_NODE (Not, not);
      
      not->addChild (getASTNode (rdcChildren[1], not));
      return not;
    }    
    
    
    // <Proposition> ::= ID
    // Proposition:Axiom := ID
    if (ind == RULE_PROPOSITION_ID) {
      CREATE_NODE (Proposition, proposition);
      proposition->addChild (getASTNode (rdcChildren[0],proposition));
      return proposition;
        }
    
    // Process Terminal Symbols (just create nodes for everyone of it, maybe
    // Convert data types from wstring to other more convenient types
  } else {
    ind = reduction->symbolIndex;
    // Terminal:
    // ID
    if (ind == SYMBOL_ID) {
      CREATE_NODE (Terminal_ID, id);
      return id;
    }
  }
  
  return searchEquivNode( rdcChildren, parent);
}
