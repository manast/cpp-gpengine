# Project: cpp-gpengine
# Makefile created by Pablo Garcia Ganzalez 
# Date: 19.10.2003

CPP  = aCC 
OBJ  = 	src/ASTCreator.o  src/ASTNode.o src/CGTFile.o src/CharacterSetTable.o src/DFA.o src/DFAStateTable.o src/ErrorReporter.o src/ErrorTable.o src/GrammarInfo.o src/LALR.o src/LALRStateTable.o src/Reduction.o src/RuleTable.o src/SymbolTable.o src/Token.o src/acc_wchar.o 
#LIBS =   
CXXINCS = -I"include/"
BIN  = lib/cpp-gpengine-1.0.3.sl
CXXFLAGS = $(CXXINCS) 

all: $(BIN) 

clean: 
	rm -f $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) -b -o $(BIN) $(OBJ)

src/ASTCreator.o: src/ASTCreator.cpp
	$(CPP) -c -AA +z src/ASTCreator.cpp -o src/ASTCreator.o $(CXXFLAGS)

src/ASTNode.o: src/ASTNode.cpp
	$(CPP) -c -AA +z src/ASTNode.cpp -o src/ASTNode.o $(CXXFLAGS)

src/CGTFile.o: src/CGTFile.cpp
	$(CPP) -c -AA +z src/CGTFile.cpp -o src/CGTFile.o $(CXXFLAGS)

src/CharacterSetTable.o: src/CharacterSetTable.cpp
	$(CPP) -c -AA +z src/CharacterSetTable.cpp -o src/CharacterSetTable.o $(CXXFLAGS)

src/DFA.o: src/DFA.cpp
	$(CPP) -c -AA +z src/DFA.cpp -o src/DFA.o $(CXXFLAGS)

src/DFAStateTable.o: src/DFAStateTable.cpp
	$(CPP) -c -AA +z src/DFAStateTable.cpp -o src/DFAStateTable.o $(CXXFLAGS)

src/ErrorReporter.o: src/ErrorReporter.cpp
	$(CPP) -c -AA +z src/ErrorReporter.cpp -o src/ErrorReporter.o $(CXXFLAGS)

src/ErrorTable.o: src/ErrorTable.cpp
	$(CPP) -c -AA +z src/ErrorTable.cpp -o src/ErrorTable.o $(CXXFLAGS)

src/GrammarInfo.o: src/GrammarInfo.cpp
	$(CPP) -c -AA +z src/GrammarInfo.cpp -o src/GrammarInfo.o $(CXXFLAGS)

src/LALR.o: src/LALR.cpp
	$(CPP) -c -AA +z src/LALR.cpp -o src/LALR.o $(CXXFLAGS)

src/LALRStateTable.o: src/LALRStateTable.cpp
	$(CPP) -c -AA +z src/LALRStateTable.cpp -o src/LALRStateTable.o $(CXXFLAGS)

src/Reduction.o: src/Reduction.cpp
	$(CPP) -c -AA +z src/Reduction.cpp -o src/Reduction.o $(CXXFLAGS)

src/RuleTable.o: src/RuleTable.cpp
	$(CPP) -c -AA +z src/RuleTable.cpp -o src/RuleTable.o $(CXXFLAGS)

src/SymbolTable.o: src/SymbolTable.cpp
	$(CPP) -c -AA +z src/SymbolTable.cpp -o src/SymbolTable.o $(CXXFLAGS)

src/Token.o: src/Token.cpp
	$(CPP) -c -AA +z src/Token.cpp -o src/Token.o $(CXXFLAGS)

src/acc_wchar.o: src/acc_wchar.cpp
	$(CPP) -c -AA +z src/acc_wchar.cpp -o src/acc_wchar.o $(CXXFLAGS)

