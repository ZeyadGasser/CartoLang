#include "parser.h"

Parser::Parser(const vector<tuple<string, string, int>>& tokensList) 
    : tokens(tokensList), currentIndex(0) {}

tuple<string, string, int> Parser::getCurrentToken() {
    if (currentIndex < tokens.size()) {
        return tokens[currentIndex];
    }
    return make_tuple("EOF", "EOF", -1);
}

void Parser::match(string expectedClass, string expectedLexeme) {
    string lexeme, tokenClass;
    int lineNumber;
    tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    
    cout << "Matched: " << lexeme << " (" << tokenClass << ")" << endl;

    if (expectedLexeme != "") {
        if (tokenClass == expectedClass && lexeme == expectedLexeme) {
            currentIndex++;
            return;
        } else {
            error("Expected '" + expectedLexeme + "' but found '" + lexeme + "'", lineNumber);
        }
    }

    if (tokenClass == expectedClass) {
        currentIndex++;
    } else {
        error("Expected " + expectedClass + " but found " + tokenClass + " '" + lexeme + "'", lineNumber);
    }
}

void Parser::error(string message, int lineNumber) {
    cerr << "Syntax Error at line " << lineNumber << ": " << message << endl;
    exit(1);
}

void Parser::semanticError(string message, int lineNumber) {
    cerr << "Semantic Error at line " << lineNumber << ": " << message << endl;
    exit(1);
}

string Parser::getTypeFromKeyword(string keyword) {
    if (keyword == "bat_num") return "int";
    if (keyword == "super_num") return "float";
    if (keyword == "Jerry_hide") return "string";
    if (keyword == "tom_char") return "char";
    if (keyword == "pinocchio") return "bool";
    return "unknown";
}

void Parser::addSymbol(string name, string type, string typeKeyword, int lineNumber, bool initialized) {
    if (symbolExists(name)) {
        semanticError("Variable '" + name + "' already declared", lineNumber);
    }
    symbolTable[name] = Symbol(name, type, typeKeyword, lineNumber, initialized);
}

bool Parser::symbolExists(string name) {
    return symbolTable.find(name) != symbolTable.end();
}

Symbol Parser::getSymbol(string name) {
    if (!symbolExists(name)) {
        return Symbol();
    }
    return symbolTable[name];
}

void Parser::markInitialized(string name) {
    if (symbolExists(name)) {
        symbolTable[name].initialized = true;
    }
}

string Parser::inferExpressionType(shared_ptr<ASTNode> node) {
    if (node->type == "NUMBER") {
        if (node->value.find('.') != string::npos) {
            return "float";
        }
        return "int";
    }
    if (node->type == "STRING_LITERAL") {
        return "string";
    }
    if (node->type == "CHAR_LITERAL") {
        return "char";
    }
    if (node->type == "BOOL_LITERAL") {
        return "bool";
    }
    if (node->type == "IDENTIFIER") {
        if (node->value == "true" || node->value == "false") {
            return "bool";
        }
        if (node->value == "0" || node->value == "1") {
            return "int";
        }
        if (symbolExists(node->value)) {
            return getSymbol(node->value).type;
        }
        return "unknown";
    }
    if (node->type == "BinaryOp" && node->children.size() == 2) {
        string leftType = inferExpressionType(node->children[0]);
        string rightType = inferExpressionType(node->children[1]);
        
        if (leftType == "float" || rightType == "float") {
            return "float";
        }
        if (leftType == "int" && rightType == "int") {
            return "int";
        }
        if (leftType == "string" && rightType == "string" && node->value == "+") {
            return "string";
        }
    }
    return "unknown";
}

void Parser::parseProgram() {
    root = make_shared<ASTNode>("Program");
    root->children.push_back(parseStatementList());
    
    string lexeme, tokenClass;
    int lineNumber;
    tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    
    if (tokenClass != "EOF") {
        error("Expected end of file", lineNumber);
    }
}

shared_ptr<ASTNode> Parser::parseStatementList() {
    auto node = make_shared<ASTNode>("StatementList");
    string lexeme, tokenClass;
    int lineNumber;
    tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    
    while (tokenClass != "EOF" && lexeme != "}") {
        node->children.push_back(parseStatement());
        tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    }
    return node;
}

shared_ptr<ASTNode> Parser::parseStatement() {
    string lexeme, tokenClass;
    int lineNumber;
    tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    
    if (tokenClass == "COMMENT") {
        return parseComment();
    }
    else if (lexeme == "bat_num" || lexeme == "super_num" || 
             lexeme == "Jerry_hide" || lexeme == "tom_char" || 
             lexeme == "pinocchio") {
        return parseDeclaration();
    }
    else if (lexeme == "sponge_bob_check") {
        return parseIfStmt();
    }
    else if (lexeme == "penguins_madagascar_repeat") {
        return parseWhileStmt();
    }
    else if (lexeme == "penguins_madagascar_iteration") {
        return parseForStmt();
    }
    else if (lexeme == "po_kungfu") {
        return parseFunctionStmt();
    }
    else if (lexeme == "po_kungfu_mastered") {
        return parseReturnStmt();
    }
    else if (lexeme == "buzz_speak") {
        return parseOutputStmt();
    }
    else if (lexeme == "buzz_receive") {
        return parseInputStmt();
    }
    else if (tokenClass == "IDENTIFIER") {
        return parseAssignment();
    }
    else if (lexeme == ";") {
        match("SYMBOL", ";");
        return make_shared<ASTNode>("EmptyStatement");
    }
    else {
        error("Unexpected token '" + lexeme + "'", lineNumber);
    }
    return nullptr;
}

shared_ptr<ASTNode> Parser::parseDeclaration() {
    string lexeme, tokenClass;
    int lineNumber;
    tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    
    auto node = make_shared<ASTNode>("Declaration");
    string typeKeyword = lexeme;
    string varType = getTypeFromKeyword(typeKeyword);
    
    auto typeNode = make_shared<ASTNode>("Type", typeKeyword);
    node->children.push_back(typeNode);
    
    match("KEYWORD");
    
    tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    string varName = lexeme;
    auto idNode = make_shared<ASTNode>("IDENTIFIER", varName);
    node->children.push_back(idNode);
    
    match("IDENTIFIER");
    
    tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    if (lexeme == "=") {
        match("SYMBOL", "=");
        auto exprNode = parseExpr();
        node->children.push_back(exprNode);
        
        string exprType = inferExpressionType(exprNode);
        if (exprType != varType && exprType != "unknown") {
            bool validConversion = false;
            
            if (varType == "float" && exprType == "int") {
                validConversion = true;
            }
            else if (varType == "bool" && exprType == "int") {
                validConversion = true;
            }
            else if (varType == "char" && exprType == "int") {
                validConversion = true;
            }
            else if (varType == "int" && exprType == "char") {
                validConversion = true;
            }
            
            if (!validConversion) {
                semanticError("Type mismatch: cannot assign " + exprType + " to " + varType, lineNumber);
            }
        }
        
        addSymbol(varName, varType, typeKeyword, lineNumber, true);
    } else {
        addSymbol(varName, varType, typeKeyword, lineNumber, false);
    }
    
    match("SYMBOL", ";");
    return node;
}

shared_ptr<ASTNode> Parser::parseAssignment() {
    string lexeme, tokenClass;
    int lineNumber;
    tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    
    auto node = make_shared<ASTNode>("Assignment");
    string varName = lexeme;
    
    if (!symbolExists(varName)) {
        semanticError("Variable '" + varName + "' not declared", lineNumber);
    }
    
    Symbol sym = getSymbol(varName);
    auto idNode = make_shared<ASTNode>("IDENTIFIER", varName);
    node->children.push_back(idNode);
    
    match("IDENTIFIER");
    tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    
    if (lexeme == "=" || lexeme == "+=" || lexeme == "-=" || 
        lexeme == "++" || lexeme == "--") {
        auto opNode = make_shared<ASTNode>("Operator", lexeme);
        node->children.push_back(opNode);
        match("SYMBOL", lexeme);
        
        if (lexeme != "++" && lexeme != "--") {
            auto exprNode = parseExpr();
            node->children.push_back(exprNode);
            
            string exprType = inferExpressionType(exprNode);
            if (exprType != sym.type && exprType != "unknown") {
                bool validConversion = false;
                
                if (sym.type == "float" && exprType == "int") {
                    validConversion = true;
                }
                else if (sym.type == "bool" && exprType == "int") {
                    validConversion = true;
                }
                else if (sym.type == "char" && exprType == "int") {
                    validConversion = true;
                }
                else if (sym.type == "int" && exprType == "char") {
                    validConversion = true;
                }
                
                if (!validConversion) {
                    semanticError("Type mismatch: cannot assign " + exprType + " to " + sym.type, lineNumber);
                }
            }
        }
        
        markInitialized(varName);
    }
    
    match("SYMBOL", ";");
    return node;
}

shared_ptr<ASTNode> Parser::parseIfStmt() {
    string lexeme, tokenClass;
    int lineNumber;
    
    auto node = make_shared<ASTNode>("IfStatement");
    
    match("KEYWORD");
    match("SYMBOL", "(");
    node->children.push_back(parseCondition());
    match("SYMBOL", ")");
    match("SYMBOL", "{");
    node->children.push_back(parseStatementList());
    match("SYMBOL", "}");
    
    tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    if (lexeme == "sponge_bob_try_again") {
        match("KEYWORD");
        match("SYMBOL", "{");
        node->children.push_back(parseStatementList());
        match("SYMBOL", "}");
    }
    
    return node;
}

shared_ptr<ASTNode> Parser::parseWhileStmt() {
    auto node = make_shared<ASTNode>("WhileStatement");
    
    match("KEYWORD");
    match("SYMBOL", "(");
    node->children.push_back(parseCondition());
    match("SYMBOL", ")");
    match("SYMBOL", "{");
    node->children.push_back(parseStatementList());
    match("SYMBOL", "}");
    
    return node;
}

shared_ptr<ASTNode> Parser::parseForStmt() {
    string lexeme, tokenClass;
    int lineNumber;
    
    auto node = make_shared<ASTNode>("ForStatement");
    
    match("KEYWORD");
    match("SYMBOL", "(");
    node->children.push_back(parseDeclaration());
    match("SYMBOL", ";");
    node->children.push_back(parseCondition());
    match("SYMBOL", ";");
    
    tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    string varName = lexeme;
    
    if (!symbolExists(varName)) {
        semanticError("Variable '" + varName + "' not declared", lineNumber);
    }
    
    auto updateNode = make_shared<ASTNode>("Update");
    auto idNode = make_shared<ASTNode>("IDENTIFIER", varName);
    updateNode->children.push_back(idNode);
    
    match("IDENTIFIER");
    tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    if (lexeme == "=" || lexeme == "+=" || lexeme == "-=" || 
        lexeme == "++" || lexeme == "--") {
        auto opNode = make_shared<ASTNode>("Operator", lexeme);
        updateNode->children.push_back(opNode);
        match("SYMBOL", lexeme);
        if (lexeme != "++" && lexeme != "--") {
            updateNode->children.push_back(parseExpr());
        }
    }
    
    node->children.push_back(updateNode);
    
    match("SYMBOL", ")");
    match("SYMBOL", "{");
    node->children.push_back(parseStatementList());
    match("SYMBOL", "}");
    
    return node;
}

shared_ptr<ASTNode> Parser::parseFunctionStmt() {
    string lexeme, tokenClass;
    int lineNumber;
    
    auto node = make_shared<ASTNode>("FunctionDeclaration");
    
    match("KEYWORD");
    tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    
    if (lexeme == "to_infinity") {
        auto typeNode = make_shared<ASTNode>("ReturnType", "void");
        node->children.push_back(typeNode);
        match("KEYWORD");
    } else {
        auto nameNode = make_shared<ASTNode>("FunctionName", lexeme);
        node->children.push_back(nameNode);
        match("IDENTIFIER");
    }
    
    match("SYMBOL", "(");
    match("SYMBOL", ")");
    match("SYMBOL", "{");
    node->children.push_back(parseStatementList());
    match("SYMBOL", "}");
    
    return node;
}

shared_ptr<ASTNode> Parser::parseReturnStmt() {
    auto node = make_shared<ASTNode>("ReturnStatement");
    
    match("KEYWORD");
    node->children.push_back(parseExpr());
    match("SYMBOL", ";");
    
    return node;
}

shared_ptr<ASTNode> Parser::parseCondition() {
    auto node = make_shared<ASTNode>("Condition");
    
    node->children.push_back(parseExpr());
    node->children.push_back(parseRelOp());
    node->children.push_back(parseExpr());
    
    return node;
}

shared_ptr<ASTNode> Parser::parseExpr() {
    string lexeme, tokenClass;
    int lineNumber;
    
    auto left = parseTerm();
    tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    
    while (lexeme == "+" || lexeme == "-") {
        auto opNode = make_shared<ASTNode>("BinaryOp", lexeme);
        match("SYMBOL", lexeme);
        auto right = parseTerm();
        
        opNode->children.push_back(left);
        opNode->children.push_back(right);
        left = opNode;
        
        tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    }
    
    return left;
}

shared_ptr<ASTNode> Parser::parseTerm() {
    string lexeme, tokenClass;
    int lineNumber;
    
    auto left = parseFactor();
    tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    
    while (lexeme == "*" || lexeme == "/" || lexeme == "%") {
        auto opNode = make_shared<ASTNode>("BinaryOp", lexeme);
        match("SYMBOL", lexeme);
        auto right = parseFactor();
        
        opNode->children.push_back(left);
        opNode->children.push_back(right);
        left = opNode;
        
        tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    }
    
    return left;
}

shared_ptr<ASTNode> Parser::parseFactor() {
    string lexeme, tokenClass;
    int lineNumber;
    tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    
    if (tokenClass == "NUMBER") {
        auto node = make_shared<ASTNode>("NUMBER", lexeme);
        match("NUMBER");
        return node;
    }
    else if (tokenClass == "IDENTIFIER") {
        if (lexeme == "true" || lexeme == "false") {
            auto node = make_shared<ASTNode>("BOOL_LITERAL", lexeme);
            match("IDENTIFIER");
            return node;
        }
        
        auto node = make_shared<ASTNode>("IDENTIFIER", lexeme);
        match("IDENTIFIER");
        return node;
    }
    else if (tokenClass == "STRING_LITERAL") {
        auto node = make_shared<ASTNode>("STRING_LITERAL", lexeme);
        match("STRING_LITERAL");
        return node;
    }
    else if (tokenClass == "CHAR_LITERAL") {
        auto node = make_shared<ASTNode>("CHAR_LITERAL", lexeme);
        match("CHAR_LITERAL");
        return node;
    }
    else if (lexeme == "(") {
        match("SYMBOL", "(");
        auto node = parseExpr();
        match("SYMBOL", ")");
        return node;
    }
    else {
        error("Expected number, identifier, string, char literal, or '(' in expression", lineNumber);
    }
    return nullptr;
}

shared_ptr<ASTNode> Parser::parseOutputStmt() {
    auto node = make_shared<ASTNode>("OutputStatement");
    
    match("KEYWORD");
    match("SYMBOL", "(");
    node->children.push_back(parseExpr());
    match("SYMBOL", ")");
    match("SYMBOL", ";");
    
    return node;
}

shared_ptr<ASTNode> Parser::parseInputStmt() {
    string lexeme, tokenClass;
    int lineNumber;
    
    auto node = make_shared<ASTNode>("InputStatement");
    
    match("KEYWORD");
    match("SYMBOL", "(");
    
    tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    string varName = lexeme;
    
    if (!symbolExists(varName)) {
        semanticError("Variable '" + varName + "' not declared", lineNumber);
    }
    
    markInitialized(varName);
    
    auto idNode = make_shared<ASTNode>("IDENTIFIER", varName);
    node->children.push_back(idNode);
    
    match("IDENTIFIER");
    match("SYMBOL", ")");
    match("SYMBOL", ";");
    
    return node;
}

shared_ptr<ASTNode> Parser::parseComment() {
    auto node = make_shared<ASTNode>("Comment");
    match("COMMENT");
    return node;
}

shared_ptr<ASTNode> Parser::parseRelOp() {
    string lexeme, tokenClass;
    int lineNumber;
    tie(lexeme, tokenClass, lineNumber) = getCurrentToken();
    
    if (lexeme == "==" || lexeme == "!=" || lexeme == "<" || 
        lexeme == ">" || lexeme == "<=" || lexeme == ">=") {
        auto node = make_shared<ASTNode>("RelOp", lexeme);
        match("SYMBOL", lexeme);
        return node;
    } else {
        error("Expected relational operator (==, !=, <, >, <=, >=)", lineNumber);
    }
    return nullptr;
}

void Parser::printTree(shared_ptr<ASTNode> node, string prefix, bool isLast) {
    if (!node) return;
    
    cout << prefix;
    if (isLast) {
        cout << "+-- ";
        prefix += "    ";
    } else {
        cout << "|-- ";
        prefix += "|   ";
    }
    
    cout << node->type;
    if (!node->value.empty()) {
        cout << ": " << node->value;
    }
    cout << endl;
    
    for (size_t i = 0; i < node->children.size(); i++) {
        printTree(node->children[i], prefix, i == node->children.size() - 1);
    }
}

void Parser::printParseTree() {
    cout << "\n========== Parse Tree ==========" << endl;
    if (root) {
        cout << root->type << endl;
        for (size_t i = 0; i < root->children.size(); i++) {
            printTree(root->children[i], "", i == root->children.size() - 1);
        }
    }
    cout << "================================" << endl;
}

void Parser::printSymbolTable() {
    cout << "\n========== Symbol Table ==========" << endl;
    cout << "Variable Name   | Type            | Line | Initialized" << endl;
    cout << "-----------------------------------------------------------" << endl;
    for (const auto& entry : symbolTable) {
        const Symbol& sym = entry.second;
        cout << sym.name;
        for (int i = sym.name.length(); i < 16; i++) cout << " ";
        cout << "| " << sym.typeKeyword;
        for (int i = sym.typeKeyword.length(); i < 16; i++) cout << " ";
        cout << "| " << sym.lineNumber;
        for (int i = to_string(sym.lineNumber).length(); i < 5; i++) cout << " ";
        cout << "| " << (sym.initialized ? "Yes" : "No") << endl;
    }
    cout << "==========================================================" << endl;
}