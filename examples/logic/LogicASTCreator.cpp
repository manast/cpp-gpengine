

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
      Start *start = new Start ();
      start->init (reduction, parent);
      
      start->addChild (getASTNode(rdcChildren[1], start));
      return start;
    }
    
    // <AxiomList> ::= <Axiom> <AxiomList>
    // AxiomList := Axiom*
    if (ind == RULE_AXIOMLIST) {
      AxiomList *axiomList = new AxiomList ();
      axiomList->init (reduction, parent);
      
      axiomList->addChild (getASTNode (rdcChildren[0], axiomList));
      
      children = axiomList->getChildren();
      getASTNodeList (children, (NonTerminal*) rdcChildren[1], 1, 2, 
		      axiomList); 
      return axiomList;
    }
    
    // <Implication> ::= <DoubleImplication> '->' <Implication>
    // Implication:Axiom := Axiom Axiom
    if (ind == RULE_IMPLICATION_MINUSGT) {
      Implication *implication = new Implication ();
      implication->init (reduction, parent);
      
      implication->addChild (getASTNode (rdcChildren[0], implication));
      implication->addChild (getASTNode (rdcChildren[2], implication));
      return implication;
    }
    
    // <DoubleImplication> ::= <Or> '<->' <DoubleImplication>
    // DoubleImplication:Axiom := Axiom Axiom
    if (ind == RULE_DOUBLEIMPLICATION_LTMINUSGT) {
      DoubleImplication *doubleImplication = new DoubleImplication ();
      doubleImplication->init (reduction, parent);
      
      doubleImplication->addChild (getASTNode (rdcChildren[0], 
					       doubleImplication));
      doubleImplication->addChild (getASTNode (rdcChildren[2], 
					       doubleImplication));
      return doubleImplication;
    }
    
    // <Or> ::= <And> OR <Or>
    // Or:Axiom := Axiom Axiom
    if (ind == RULE_OR_OR) {
      Or *_or = new Or ();
      _or->init (reduction, parent);
      
      _or->addChild (getASTNode (rdcChildren[0], _or));
      _or->addChild (getASTNode (rdcChildren[2], _or));
      return _or;
    }
    
    // <And> ::= <Not> AND <And>
    // And:Axiom := Axiom Axiom
    if (ind == RULE_AND_AND) {
      And *_and = new And ();
      _and->init (reduction, parent);
      
      _and->addChild (getASTNode (rdcChildren[0], _and));
      _and->addChild (getASTNode (rdcChildren[2], _and));
      return _and;
    }
    
    // <Not> ::= NOT <Value> 
    // Not:Axiom := Axiom
    if (ind == RULE_NOT_NOT) {
      Not *_not = new Not ();
      _not->init (reduction, parent);
      
      _not->addChild (getASTNode (rdcChildren[1], _not));
      return _not;
    }    
    
    
    // <Proposition> ::= ID
    // Proposition:Axiom := ID
    if (ind == RULE_PROPOSITION_ID) {
      Proposition *proposition = new Proposition ();
      proposition->init (reduction, parent);
      proposition->addChild (getASTNode (rdcChildren[0],proposition));
      return proposition;
        }
    
    // Process Terminal Symbols (just create nodes for everyone of it, maybe also
    // convert data types from wstring to other more convenient types)
  } else {
    ind = reduction->symbolIndex;
    // Terminal:
    // ID
    if (ind == SYMBOL_ID) {
      Terminal_ID *id = new Terminal_ID ();
      id->init (reduction, parent);
      return id;
    }
  }
  
  // Search for equivalent nodes among the childrens of this reduction
  return searchEquivNode( rdcChildren, parent);
}
