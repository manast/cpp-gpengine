

#include <stdlib.h>

class testErrorRep : public ErrorReporter {
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
                itoa (sym->line, tmpbuf, 10);
                header += tmpbuf;
                header += ",";
                itoa (sym->col, tmpbuf, 10);
                header += tmpbuf;
                msg = " if statement is missing end";

                return header + msg;
            } 
        }
      
        // while without end  
        sym = in (L"while", err.traceback, &pos); 
        if (sym != 0) {
            if (in (L"end", err.expected, &pos)) {
                itoa (sym->line, tmpbuf, 10);
                header += tmpbuf;
                header += ",";
                itoa (sym->col, tmpbuf, 10);
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
                itoa (err.lastTerminal.line, tmpbuf, 10);
                header += tmpbuf;
                header += ",";
                itoa (err.lastTerminal.col, tmpbuf, 10);
                header += tmpbuf;
                msg = " EOF reached but not end found";

                return header + msg;
            }
        }
        
        // Missing NEWLINE
        if (in (L"NEWLINE", err.expected, &pos)) {
                itoa (err.lastTerminal.line, tmpbuf, 10);
                header += tmpbuf;
                header += ",";
                itoa (err.lastTerminal.col, tmpbuf, 10);
                header += tmpbuf;
                msg = " a carry return is missing";

                return header + msg;
        }
        
        // Default error
        itoa (err.lastTerminal.line, tmpbuf, 10);
        header += tmpbuf;
        header += ",";
        itoa (err.lastTerminal.col, tmpbuf, 10);
        
        header += tmpbuf;
        msg = " unexpected token ";
        //msg = err.lastTerminal.image;

        return header + msg;
    }
};

  