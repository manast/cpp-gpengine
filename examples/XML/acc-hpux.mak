# Project: cpp-gpengine
# Makefile created by Pablo Garcia Ganzalez 
# Date: 10.11.2003

CPP  =  aCC 
OBJ  = 	XML.o 
GPENGINELIB = ../../lib/cpp-gpengine-1.0.4.sl   
LIBS = -L"../../lib" 
CXXINCS = -I"../../include/" -I"/usr/include" 
BIN  = XML
CXXFLAGS = -AA -D_XOPEN_SOURCE=500 $(CXXINCS) 

all: XML 

clean: 
	rm -f $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(OBJ) $(GPENGINELIB) -AA -o "XML" $(LIBS)

XML.o: XML.cpp
	$(CPP) -c XML.cpp -o XML.o $(CXXFLAGS)


