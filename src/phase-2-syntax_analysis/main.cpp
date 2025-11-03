#include <iostream>
#include "C:\Users\zeadg\OneDrive\Desktop\CartoLang\src\phase-1-lexical_analysis\lexer.h"
#include "C:\Users\zeadg\OneDrive\Desktop\CartoLang\src\phase-2-syntax_analysis\parser.h"

using namespace std;

int main() {
    cout << "=== CartoLang Compiler ===" << endl << endl;

        Lexer lexer;
        const vector<tuple<string, string, int>>& tokens = lexer.GetTokenList();
        
        cout << "\nTokens generated: " << tokens.size() << endl;
        
        cout << "\n--- Starting Parser ---\n" << endl;
        Parser parser(tokens);
        parser.parseProgram();
        cout << "\n=== Compilation Successful ===" << endl;

   

    return 0;
}