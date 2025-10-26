#ifndef LEXER_H
#define LEXER_H

#include<iostream>
#include<regex>
#include <fstream>
#include "token.h"
using namespace std;

class Lexer{
public:
Lexer();
void ReadFile();
void Tokenize(const string& line,int lineNumber);
const vector<tuple<string, string, int>>& GetTokenList()const;
private:
Token token;
vector<tuple<string, string, int>> tokensList;

    regex commentRegex; 
    regex keywordRegex; 
    regex symbolRegex;
    regex numberRegex;
    regex identifierRegex;
    regex stringLiteralRegex;
};


#endif 

