enum SymbolConstants
{
   SYMBOL_EOF               = 0 , // (EOF)
   SYMBOL_ERROR             = 1 , // (Error)
   SYMBOL_WHITESPACE        = 2 , // (Whitespace)
   SYMBOL_COMMENTEND        = 3 , // (Comment End)
   SYMBOL_COMMENTLINE       = 4 , // (Comment Line)
   SYMBOL_COMMENTSTART      = 5 , // (Comment Start)
   SYMBOL_LPARAN            = 6 , // '('
   SYMBOL_RPARAN            = 7 , // ')'
   SYMBOL_LTMINUSGT         = 8 , // '<->'
   SYMBOL_MINUSGT           = 9 , // '->'
   SYMBOL_AND               = 10, // AND
   SYMBOL_ID                = 11, // ID
   SYMBOL_NEWLINE           = 12, // NEWLINE
   SYMBOL_NOT               = 13, // NOT
   SYMBOL_OR                = 14, // OR
   SYMBOL_AXIOM             = 16, // <Axiom>
   SYMBOL_AXIOMLIST         = 17, // <AxiomList>
   SYMBOL_DOUBLEIMPLICATION = 18, // <DoubleImplication>
   SYMBOL_IMPLICATION       = 19, // <Implication>
   SYMBOL_NEWLINELIST       = 20, // <NewLineList>
   SYMBOL_NEWLINES          = 21, // <NewLines>
   SYMBOL_PROPOSITION       = 24, // <Proposition>
   SYMBOL_START             = 25, // <Start>
   SYMBOL_VALUE             = 26 // <Value>
};

enum RuleConstants
{
   RULE_START                       = 0 , // <Start> ::= <NewLineList> <AxiomList>
   RULE_NEWLINES_NEWLINE            = 1 , // <NewLines> ::= NEWLINE <NewLineList>
   RULE_NEWLINELIST_NEWLINE         = 2 , // <NewLineList> ::= NEWLINE <NewLineList>
   RULE_NEWLINELIST                 = 3 , // <NewLineList> ::= 
   RULE_AXIOMLIST                   = 4 , // <AxiomList> ::= <Axiom> <AxiomList>
   RULE_AXIOMLIST2                  = 5 , // <AxiomList> ::= 
   RULE_AXIOM                       = 6 , // <Axiom> ::= <Implication> <NewLines>
   RULE_IMPLICATION_MINUSGT         = 7 , // <Implication> ::= <DoubleImplication> '->' <Implication>
   RULE_IMPLICATION                 = 8 , // <Implication> ::= <DoubleImplication>
   RULE_DOUBLEIMPLICATION_LTMINUSGT = 9 , // <DoubleImplication> ::= <Or> '<->' <DoubleImplication>
   RULE_DOUBLEIMPLICATION           = 10, // <DoubleImplication> ::= <Or>
   RULE_OR_OR                       = 11, // <Or> ::= <And> OR <Or>
   RULE_OR                          = 12, // <Or> ::= <And>
   RULE_AND_AND                     = 13, // <And> ::= <Not> AND <And>
   RULE_AND                         = 14, // <And> ::= <Not>
   RULE_NOT_NOT                     = 15, // <Not> ::= NOT <Value>
   RULE_NOT                         = 16, // <Not> ::= <Value>
   RULE_VALUE_LPARAN_RPARAN         = 17, // <Value> ::= '(' <Implication> ')'
   RULE_VALUE                       = 18, // <Value> ::= <Proposition>
   RULE_PROPOSITION_ID              = 19 // <Proposition> ::= ID
};
