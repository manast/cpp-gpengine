

#include <stdlib.h>
#include "ErrorReporter.h"
using namespace std;

class SimpleErrorRep : public ErrorReporter {
    string composeParseErrorMsg (const GPError &err) {
        string header = "error at ";
        string msg;
        Symbol *sym;
       
        // Check for if without end
        int pos;

        // We have different conditions. If one of them is satisfied we generate the error
        // message for it.
  
        // If without end
        sym = in (L"if", err.traceback, &pos); 
        if (sym != 0) {
            if (in (L"end", err.expected, &pos)) {
                header += atoi (sym->line);
                header += ","; 	
                header += atoi (sym->col);
                msg = ": if statement is missing end";
                return header + msg;
            } 
        }
      
        // while without end  
        sym = in (L"while", err.traceback, &pos); 
        if (sym != 0) {
            if (in (L"end", err.expected, &pos)) {
                header += atoi (sym->line);
                header += ":";
                header += atoi (sym->col);
                msg = ": while statement is missing end";
                return header + msg;
            } 
        }
       
        
        // Default error
        header += atoi (err.lastTerminal.line);
        header += ":";
        header += atoi (err.lastTerminal.col);
        msg = " unexpected token ";
     //   msg += err.lastTerminal.image;

        return header + msg;
    }
};

 
 
