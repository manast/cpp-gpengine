/***************************************************************************
                          ErrorReporter.cpp  -  
                          Reports the errors in a human readable 
                          way.
                          --------------------------------------
    begin                : Sat Sep 20 2003
    copyright            : (C) 2002-2003 Manuel Astudillo

 ***************************************************************************/

 /***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/


#include "ErrorReporter.h"

ErrorReporter::ErrorReporter () {
    // Default Error Messages
    endComment = "EOF Reached but end of comment was not found";
    unknownToken = "unknown token";
}

ErrorReporter::~ErrorReporter () {

}

string ErrorReporter::composeErrorMsg (const GPError &err) {
    switch (err.type) {
    case ERROR_SCAN:
        return composeScanErrorMsg (err);
        break;
    case ERROR_PARSE:
        // This has to be a more complex function that process
        // the traceback in order to give a better error
        return composeParseErrorMsg (err);
        break;
    }
    return "";
}

string ErrorReporter::composeScanErrorMsg (const GPError &err) {
    switch (err.value) {
        case END_COMMENT_NOT_FOUND:
            return composeLineCol (err) + endComment;
            break;
        case UNKNOWN_TOKEN:
            return composeLineCol (err) + unknownToken;
            break;
        }
    return "";
}

// This is the function that has to be strongly customized for every application.
string ErrorReporter::composeParseErrorMsg (const GPError &err) {
    // Default Parse Error
    return composeLineCol (err) + "error parsing file";
}

wstring ErrorReporter::composeScanErrorMsgU  (const GPError &err) {
    return L"";
}

wstring ErrorReporter::composeParseErrorMsgU (const GPError &err) {
    return L"";
}

bool ErrorReporter::in (wstring a, vector<wstring> expected, int *pos) {
    for (unsigned int i = 0; i < expected.size(); i ++) {
        if (a == expected[i]) {
            *pos = i;
            return true;
        }
    }
    *pos = -1;
    return false;
}

Symbol *ErrorReporter::in (wstring a, vector <Symbol*> traceback, int *pos) {
    for (unsigned int i = 0; i < traceback.size(); i ++) {
        wstring b = traceback[i]->symbol;
        if (a == b) {
            *pos = i;
            return traceback[i];
        }
    }
    *pos = -1;
    return NULL;
}

string ErrorReporter::atoi (int i) {
    char tmpbuf[10];
    sprintf(tmpbuf, "%i", i);
    return tmpbuf;
}

string ErrorReporter::composeLineCol (const GPError &err) {
    return atoi (err.line) + ":" + atoi (err.col) + ":";
}

