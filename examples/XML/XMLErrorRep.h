

#include <stdlib.h>

using namespace std;

class XMLErrorRep : public ErrorReporter {
    string composeParseErrorMsg (const GPError &err) {
        string header = "Error at ";
        string msg;
        Symbol *sym;

        char tmpbuf[10];
       

        // Check for if without end
        int pos;

        // We have different conditions. If one of them is satisfied we generate the error
        // message for it.
  
        // If without end
        sym = in (L"if", err.traceback, &pos); 
        if (sym != 0) {
            if (in (L"end", err.expected, &pos)) {
                sprintf(tmpbuf, "%i", sym->line);
                header += tmpbuf;
                header += ",";
		sprintf(tmpbuf, "%i", sym->col); 	
                header += tmpbuf;
                msg = " if statement is missing end";
                return header + msg;
            } 
        }
      
        // while without end  
        sym = in (L"while", err.traceback, &pos); 
        if (sym != 0) {
            if (in (L"end", err.expected, &pos)) {
		sprintf(tmpbuf, "%i", sym->line);
                header += tmpbuf;
                header += ",";
		sprintf(tmpbuf, "i", sym->col);
                header += tmpbuf;
                msg = " while statement is missing end";
                return header + msg;
            } 
        }
        
        // Missing end at the end of the script
        // sym = in (L"EOF", err.traceback, &pos); 
        wstring tmp = L"EOF";
        if (tmp == err.lastTerminal.symbol) {
            if (in (L"end", err.expected, &pos)) {
		sprintf(tmpbuf, "i", err.lastTerminal.line);
                header += tmpbuf;
                header += ",";
		sprintf(tmpbuf, "%i", err.lastTerminal.col);
                header += tmpbuf;
                msg = " EOF reached but not end found";

                return header + msg;
            }
        }
        
        // Missing NEWLINE
        if (in (L"NEWLINE", err.expected, &pos)) {
		sprintf(tmpbuf, "%i", err.lastTerminal.line);
                header += tmpbuf;
                header += ",";

		sprintf(tmpbuf, "%i", err.lastTerminal.col);
                header += tmpbuf;
                msg = " a carry return is missing";

                return header + msg;
        }
        
        // Default error
	
	sprintf(tmpbuf, "%i", err.lastTerminal.line);
        header += tmpbuf;
        header += ",";
	sprintf(tmpbuf, "%i", err.lastTerminal.col);
        header += tmpbuf;
        msg = " unexpected token ";
        //msg = err.lastTerminal.image;

        return header + msg;
    }
};

 
 
