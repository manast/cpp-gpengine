

#include <stdlib.h>

class testErrorRep : public ErrorReporter {
    string composeParseErrorMsg (const GPError &err) {
        string header = "Error at ";
        string msg;
        
        char tmpbuf[10];
       

        // Check for if without end
        int pos;

        Token *tok = in (L"if", err.traceback, &pos); 
        if (tok != 0) {
            if (in (L"end", err.expected, &pos)) {
                itoa (tok->line, tmpbuf, 10);
                header += tmpbuf;
                header += ",";
                itoa (tok->col, tmpbuf, 10);
                header += tmpbuf;
                msg = " if statement is missing end";

                return header + msg;
            }
        }
    }
};

  