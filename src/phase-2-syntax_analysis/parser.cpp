#include "parser.h"

Parser::Parser(const vector<tuple<string, string, int>>& tokensList) 
    : tokens(tokensList), currentIndex(0) {}

/************************************************************************************************* */
tuple<string, string, int> Parser::getCurrentToken() {
    if (currentIndex < tokens.size()) {
        return tokens[currentIndex];
    }
    return make_tuple("EOF", "EOF", -1);
}
/************************************************************************************************* */
void Parser::match(string expectedClass) {
    string lexeme, tokenClass;
    int lineNumber;
    tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    
    if (tokenClass == expectedClass) {
        cout << "Matched: " << lexeme << " (" << tokenClass << ")" << endl;
        currentIndex++;
    } else {
        error("Expected " + expectedClass + " but found " + tokenClass + " '" + lexeme + "'", lineNumber);
    }
}
/************************************************************************************************* */
void Parser::error(string message, int lineNumber) {
    cerr << "Syntax Error at line " << lineNumber << ": " << message << endl;
    exit(1);
}
/************************************************************************************************* */
void Parser::parseProgram() {
    cout << "Starting parsing..." << endl;
    parseStatementList();
    
    string lexeme, tokenClass;
    int lineNumber;
    tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    
    if (tokenClass != "EOF") {
        error("Expected end of file", lineNumber);
    }
    
    cout << "Parsing completed successfully!" << endl;
}
/************************************************************************************************* */
// StatementList → Statement StatementList | ε
void Parser::parseStatementList() {
    string lexeme, tokenClass;
    int lineNumber;
    tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    
    while (tokenClass != "EOF" && lexeme != "}") {
        parseStatement();
        tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    }
}
/************************************************************************************************* */

void Parser::parseStatement() {
    string lexeme, tokenClass;
    int lineNumber;
    tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    
    if (tokenClass == "COMMENT") {
        parseComment();
    }
    else if (lexeme == "bat_num" || lexeme == "super_num" || 
             lexeme == "Jerry_hide" || lexeme == "tom_char" || 
             lexeme == "pinocchio") {
        parseDeclaration();
    }
    else if (lexeme == "sponge_bob_check") {
        parseIfStmt();
    }
    else if (lexeme == "penguins_madagascar_repeat") {
        parseWhileStmt();
    }
    else if (lexeme == "penguins_madagascar_iteration") {
        parseForStmt();
    }
    else if (lexeme == "po_kungfu") {
        parseFunctionStmt();
    }
    else if (lexeme == "po_kungfu_mastered") {
        parseReturnStmt();
    }
    else if (lexeme == "buzz_speak") {
        parseOutputStmt();
    }
    else if (lexeme == "buzz_receive") {
        parseInputStmt();
    }
    else if (tokenClass == "IDENTIFIER") {
        parseAssignment();
    }
    else if (lexeme == ";") {
        match("SYMBOL");
    }
    else {
        error("Unexpected token '" + lexeme + "'", lineNumber);
    }
}

// Declaration
void Parser::parseDeclaration() {
    string lexeme, tokenClass;
    int lineNumber;
    
    match("KEYWORD");
    match("IDENTIFIER");
    
    tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    if (lexeme == "=") {
        match("SYMBOL");
        parseExpr();
    }
    
    match("SYMBOL");
}

// Assignment
void Parser::parseAssignment() {
    string lexeme, tokenClass;
    int lineNumber;
    
    match("IDENTIFIER");
    tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    
    if (lexeme == "=" || lexeme == "+=" || lexeme == "-=" || 
        lexeme == "++" || lexeme == "--") {
        match("SYMBOL");
        
        if (lexeme != "++" && lexeme != "--") {
            parseExpr();
        }
    }
    
    match("SYMBOL");
}

// IfStmt
void Parser::parseIfStmt() {
    string lexeme, tokenClass;
    int lineNumber;
    
    match("KEYWORD");
    match("SYMBOL");
    parseCondition();
    match("SYMBOL");
    match("SYMBOL");
    parseStatementList();
    match("SYMBOL");
    
    tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    if (lexeme == "sponge_bob_try_again") {
        match("KEYWORD");
        match("SYMBOL");
        parseStatementList();
        match("SYMBOL");
    }
}

// WhileStmt
void Parser::parseWhileStmt() {
    match("KEYWORD");
    match("SYMBOL");
    parseCondition();
    match("SYMBOL");
    match("SYMBOL");
    parseStatementList();
    match("SYMBOL");
}

// ForStmt
void Parser::parseForStmt() {
    string lexeme, tokenClass;
    int lineNumber;
    
    match("KEYWORD");
    match("SYMBOL");
    parseDeclaration();
    match("SYMBOL");
    parseCondition();
    match("SYMBOL");
    
    match("IDENTIFIER");
    tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    if (lexeme == "=" || lexeme == "+=" || lexeme == "-=" || 
        lexeme == "++" || lexeme == "--") {
        match("SYMBOL");
        if (lexeme != "++" && lexeme != "--") {
            parseExpr();
        }
    }
    
    match("SYMBOL");
    match("SYMBOL");
    parseStatementList();
    match("SYMBOL");
}

// FunctionStmt
void Parser::parseFunctionStmt() {
    string lexeme, tokenClass;
    int lineNumber;
    
    match("KEYWORD");
    tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    
    if (lexeme == "to_infinity") {
        match("KEYWORD");
    } else {
        match("IDENTIFIER");
    }
    
    match("SYMBOL");
    match("SYMBOL");
    match("SYMBOL");
    parseStatementList();
    match("SYMBOL");
}

// ReturnStmt
void Parser::parseReturnStmt() {
    match("KEYWORD");
    parseExpr();
    match("SYMBOL");
}

// Condition
void Parser::parseCondition() {
    parseExpr();
    parseRelOp();
    parseExpr();
}

// Expr
void Parser::parseExpr() {
    string lexeme, tokenClass;
    int lineNumber;
    
    parseTerm();
    tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    
    while (lexeme == "+" || lexeme == "-") {
        match("SYMBOL");
        parseTerm();
        tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    }
}

// Term
void Parser::parseTerm() {
    string lexeme, tokenClass;
    int lineNumber;
    
    parseFactor();
    tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    
    while (lexeme == "*" || lexeme == "/" || lexeme == "%") {
        match("SYMBOL");
        parseFactor();
        tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    }
}

// Factor
void Parser::parseFactor() {
    string lexeme, tokenClass;
    int lineNumber;
    tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    
    if (tokenClass == "NUMBER") {
        match("NUMBER");
    }
    else if (tokenClass == "IDENTIFIER") {
        match("IDENTIFIER");
    }
    else if (tokenClass == "STRING_LITERAL") {
        match("STRING_LITERAL");
    }
    else if (lexeme == "(") {
        match("SYMBOL");
        parseExpr();
        match("SYMBOL");
    }
    else {
        error("Expected number, identifier, string, or '(' in expression", lineNumber);
    }
}

// OutputStmt
void Parser::parseOutputStmt() {
    match("KEYWORD");
    match("SYMBOL");
    parseExpr();
    match("SYMBOL");
    match("SYMBOL");
}

// InputStmt
void Parser::parseInputStmt() {
    match("KEYWORD");
    match("SYMBOL");
    match("IDENTIFIER");
    match("SYMBOL");
    match("SYMBOL");
}

// Comment
void Parser::parseComment() {
    match("COMMENT");
}

// RelOp
void Parser::parseRelOp() {
    string lexeme, tokenClass;
    int lineNumber;
    tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    
    if (lexeme == "==" || lexeme == "!=" || lexeme == "<" || 
        lexeme == ">" || lexeme == "<=" || lexeme == ">=") {
        match("SYMBOL");
    } else {
        error("Expected relational operator (==, !=, <, >, <=, >=)", lineNumber);
    }
}