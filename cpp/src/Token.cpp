# include "Token.h"


Token::Token (TokenType type, string lexeme, Object *literal, int line) {
    this -> type = type;
    this -> lexeme = lexeme;
    this -> line = line;
    this -> literal = literal;
}

string Token::toString () {
    return this -> type + " " + this -> lexeme + " " + this -> literal -> toString();
}