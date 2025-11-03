#include "lexer.h"
Lexer::Lexer() 
    : commentRegex(R"(~.*)"),
      keywordRegex(R"(\b(po_kungfu_mastered|po_kungfu|to_infinity|bat_num|super_num|Jerry_hide|tom_char|pinocchio|buzz_speak|buzz_receive|sponge_bob_check|sponge_bob_try_again|penguins_madagascar_repeat|penguins_madagascar_iteration|mickey_mouse_include|buzz_zone)\b)"),
      symbolRegex(R"((\+\+|--|\+=|-=|<=|>=|==|!=)|[\{\}\(\)\[\];:,.=+\*/%<>~\-])"),
      numberRegex(R"([0-9]+)"),
      identifierRegex(R"([A-Za-z_][A-Za-z0-9_]*)"),
      stringLiteralRegex(R"("([^"\\]|\\.)*")")
      {
        ReadFile();
}

//***************************************************************************************/
void Lexer::ReadFile(){
    try
    {
        ifstream file(R"(C:\Users\zeadg\OneDrive\Desktop\CartoLang\tests\lexer_test_1.cl)");
        if(!file.is_open()){
            throw runtime_error("Failed to open file!\n");
        }
        else{
            cout << "File opened successfully!\n";
            string line;
            int lineNumber=1;
            while(getline(file,line)){
                Tokenize(line,lineNumber++);
            }
        }
        
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }
    
}
//***************************************************************************************/
void Lexer::Tokenize(const string& line, int lineNumber) {
    smatch match;
    string word = regex_replace(line, regex("^\\s+"), ""); 

    while (!word.empty()) {
        string tokenClass;
        string lexeme;

        if (regex_search(word, match, commentRegex, regex_constants::match_continuous)) {
            lexeme = match.str();
            tokenClass = "COMMENT";
        }
        else if (regex_search(word, match, stringLiteralRegex, regex_constants::match_continuous)) {
            lexeme = match.str();
            tokenClass = "STRING_LITERAL";
        }
        else if (regex_search(word, match, symbolRegex, regex_constants::match_continuous)) {
            lexeme = match.str();
            tokenClass = token.SearchTokenClass(lexeme);
        }
        else if (regex_search(word, match, numberRegex, regex_constants::match_continuous)) {
            lexeme = match.str();
            tokenClass = "NUMBER";
        }
        else if (regex_search(word, match, identifierRegex, regex_constants::match_continuous)) {
            lexeme = match.str();
            tokenClass = token.SearchTokenClass(lexeme);
        }
        else {
            lexeme = word.substr(0, 1);
            tokenClass = "UNKNOWN";
            tokensList.push_back({lexeme, tokenClass, lineNumber});
            word = word.substr(1);
            continue;
        }

        tokensList.push_back({lexeme, tokenClass, lineNumber});
        word = match.suffix().str();
        word = regex_replace(word, regex("^\\s+"), "");
    }
}

//***************************************************************************************/

const vector<tuple<string, string, int>>& Lexer::GetTokenList()const{
return tokensList;
}
