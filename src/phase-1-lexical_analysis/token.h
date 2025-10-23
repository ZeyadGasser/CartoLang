#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class Token {
public:
    Token();

private:
    string tokenClass;
    string lexeme;
    unordered_map<string, string> tokens;

    void loadToken();
};

#endif 
