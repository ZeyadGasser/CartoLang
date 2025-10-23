#include "token.h"
Token::Token(){
    
    loadToken();
}

void Token::loadToken() {
    // Program & Function
    tokens["to_infinity"] = "KEYWORD";
    tokens["po_kungfu"] = "KEYWORD";
    tokens["po_kungfu_mastered"] = "KEYWORD";

    // Variables
    tokens["bat_num"] = "KEYWORD";
    tokens["super_num"] = "KEYWORD";
    tokens["Jerry_hide"] = "KEYWORD";
    tokens["tom_char"] = "KEYWORD";
    tokens["pinocchio"] = "KEYWORD";

    // Input/Output
    tokens["buzz_speak"] = "KEYWORD";
    tokens["buzz_receive"] = "KEYWORD";

    // Conditions
    tokens["sponge_bob_check"] = "KEYWORD";
    tokens["sponge_bob_try_again"] = "KEYWORD";

    // Loops
    tokens["penguins_madagascar_repeat"] = "KEYWORD";
    tokens["penguins_madagascar_iteration"] = "KEYWORD";

    // Include / Namespace
    tokens["mickey_mouse_include"] = "KEYWORD";
    tokens["buzz_zone"] = "KEYWORD";

    // Comment
    tokens["~"] = "SYMBOL";

    // General Symbols
    tokens["{"] = "SYMBOL";
    tokens["}"] = "SYMBOL";
    tokens["("] = "SYMBOL";
    tokens[")"] = "SYMBOL";
    tokens["["] = "SYMBOL";
    tokens["]"] = "SYMBOL";
    tokens[";"] = "SYMBOL";
    tokens[":"] = "SYMBOL";
    tokens[","] = "SYMBOL";
    tokens["."] = "SYMBOL";
    tokens["="] = "SYMBOL";
    tokens["+"] = "SYMBOL";
    tokens["-"] = "SYMBOL";
    tokens["*"] = "SYMBOL";
    tokens["/"] = "SYMBOL";
    tokens["%"] = "SYMBOL";
    tokens["<"] = "SYMBOL";
    tokens[">"] = "SYMBOL";
    tokens["<="] = "SYMBOL";
    tokens[">="] = "SYMBOL";
    tokens["=="] = "SYMBOL";
    tokens["!="] = "SYMBOL";

    cout << "Tokens loaded successfully!" << endl;

}
