# include "Token.h"

# include <iostream>

using namespace std;


Token::Token (TokenType type, string lexeme, Object *literal, int line) {
    this -> type = type;
    this -> lexeme = lexeme;
    this -> line = line;
    this -> literal = literal;
}

Token::~Token () {
    delete literal;
}

Token& Token::operator= (const Token& other) {
    if (this == &other) {
        return *this;
    }

    type = other.type;
    lexeme = other.lexeme;
    line = other.line;

    delete literal;
    literal = nullptr;
    literal = other.literal;
    return *this;
}

Token::Token (const Token& other) {
    type = other.type;
    lexeme = other.lexeme;
    line = other.line;
    literal = other.literal;
}

string Token::getLexeme () {
    return this -> lexeme;
}

string Token::toString () {
    string literal_string = (this -> literal != NULL) ? this -> literal -> toString() : "NULL";
    return this -> type + " " + this -> lexeme + " " + literal_string;
}

TokenType Token::getType () {
    return this -> type;
}

int Token::getLine () {
    return this -> line;
}


Object* Token::getLiteral () {
    return this -> literal;
}