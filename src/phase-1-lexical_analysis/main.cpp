#include "lexer.h"
#include "token.h"
#include<iostream>


using namespace std;

int main(){
Lexer lex;
const vector<tuple<string,string,int>> tokenList = lex.GetTokenList();
 
   for (const auto& t : tokenList) {
    cout << "[" << get<0>(t) << "] --> [" << get<1>(t) 
         << "] (line " << get<2>(t) << ")" << endl;
    }

    return 0;
}