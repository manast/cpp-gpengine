# Project: cpp-gpengine
# Makefile created by Pablo Garcia Ganzalez 
# Date: 19.10.2003

CPP  = aCC 
OBJ  = 	test.o 
GPENGINELIB = ../lib/cpp-gpengine-1.0.3.sl   
LIBS = -L"../lib" 
CXXINCS = -I"../include/" -I"/usr/include" 
BIN  = test
CXXFLAGS = $(CXXINCS) 

all: test 

clean: 
	rm -f $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(OBJ) $(GPENGINELIB) -AA -o "test" $(LIBS)

test.o: test.cpp
	$(CPP) -c -AA test.cpp -o test.o $(CXXFLAGS)


