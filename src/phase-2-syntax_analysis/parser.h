#ifndef PARSER_H
#define PARSER_H

#include<iostream>
#include <vector>
#include <tuple>
#include <cstdlib>
#include "C:\Users\zeadg\OneDrive\Desktop\CartoLang\src\phase-1-lexical_analysis\token.h"
using namespace std;

class Parser{
public:
Parser(const vector<tuple<string, string, int>>& tokensList);
void parseProgram();

private:
vector<tuple<string, string, int>> tokens; // (lexeme, tokenClass, lineNumber)
int currentIndex = 0;

tuple<string, string, int> getCurrentToken();
void match(string expectedClass);
void error(string message,int lineNumber);

void parseStatementList();    
void parseStatement(); 

void parseDeclaration();
void parseAssignment();
void parseIfStmt();
void parseWhileStmt();
void parseForStmt();
void parseFunctionStmt();
void parseReturnStmt();
void parseCondition();
void parseExpr();
void parseTerm();
void parseFactor();
void parseOutputStmt();
void parseInputStmt();
void parseComment();
void parseRelOp();

};


#endif 

