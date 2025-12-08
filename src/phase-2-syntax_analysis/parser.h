#ifndef PARSER_H
#define PARSER_H

#include<iostream>
#include <vector>
#include <tuple>
#include <cstdlib>
#include <map>
#include <memory>
#include "C:\Users\zeadg\OneDrive\Desktop\CartoLang\src\phase-1-lexical_analysis\token.h"
using namespace std;

struct ASTNode {
    string type;
    string value;
    vector<shared_ptr<ASTNode>> children;
    
    ASTNode(string t, string v = "") : type(t), value(v) {}
};

struct Symbol {
    string name;
    string type;
    string typeKeyword;
    int lineNumber;
    bool initialized;
    
    Symbol(string n = "", string t = "", string tk = "", int l = 0, bool i = false) 
        : name(n), type(t), typeKeyword(tk), lineNumber(l), initialized(i) {}
};

class Parser{
public:
Parser(const vector<tuple<string, string, int>>& tokensList);
void parseProgram();
void printParseTree();
void printSymbolTable();

private:
vector<tuple<string, string, int>> tokens;
int currentIndex;
map<string, Symbol> symbolTable;
shared_ptr<ASTNode> root;

tuple<string, string, int> getCurrentToken();
void match(string expectedClass,string expectedLexeme ="");
void error(string message,int lineNumber);
void semanticError(string message, int lineNumber);

string getTypeFromKeyword(string keyword);
void addSymbol(string name, string type, string typeKeyword, int lineNumber, bool initialized);
bool symbolExists(string name);
Symbol getSymbol(string name);
void markInitialized(string name);
string inferExpressionType(shared_ptr<ASTNode> node);

void printTree(shared_ptr<ASTNode> node, string prefix, bool isLast);

shared_ptr<ASTNode> parseStatementList();
shared_ptr<ASTNode> parseStatement();
shared_ptr<ASTNode> parseDeclaration();
shared_ptr<ASTNode> parseAssignment();
shared_ptr<ASTNode> parseIfStmt();
shared_ptr<ASTNode> parseWhileStmt();
shared_ptr<ASTNode> parseForStmt();
shared_ptr<ASTNode> parseFunctionStmt();
shared_ptr<ASTNode> parseReturnStmt();
shared_ptr<ASTNode> parseCondition();
shared_ptr<ASTNode> parseExpr();
shared_ptr<ASTNode> parseTerm();
shared_ptr<ASTNode> parseFactor();
shared_ptr<ASTNode> parseOutputStmt();
shared_ptr<ASTNode> parseInputStmt();
shared_ptr<ASTNode> parseComment();
shared_ptr<ASTNode> parseRelOp();
};

#endif