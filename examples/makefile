# Project: cpp-gpengine
# Makefile created by Pablo Garcia Gonzalez 
# Date: 11.11.2003

CPP  = g++ 
OBJ  = 	test.o   
LIBS = -L"/usr/lib" -L"../lib" ../lib/cpp-gpengine-1.0.4.a  
CXXINCS = -I"../include/" -I"/usr/include" 
BIN  = test
CXXFLAGS = $(CXXINCS)  

all: test 

clean: 
	rm -f $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(OBJ) -o "test" $(LIBS)

test.o: test.cpp
	$(CPP) -c -Wall test.cpp -o test.o $(CXXFLAGS)


