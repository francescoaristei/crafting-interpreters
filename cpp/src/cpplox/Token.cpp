# include "Token.h"

# include <iostream>

using namespace std;


Token::Token (TokenType type, string lexeme, Object *literal, int line) {
    this -> type = type;
    this -> lexeme = lexeme;
    this -> line = line;
    this -> literal = literal;
}

string Token::getLexeme () {
    return this -> lexeme;
}

string Token::toString () {
    string literal_string = (this -> literal != NULL) ? this -> literal -> toString() : "NULL";
    return this -> type + " " + this -> lexeme + " " + literal_string;
}