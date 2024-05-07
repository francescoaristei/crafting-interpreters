
# ifndef TOKEN
# define TOKEN
# include "TokenType.h"
# include <stdio.h>
# include "Object.h"

using namespace std;


class Token {
    public:
        TokenType type;
        string lexeme;
        int line;
        Object *literal;
        Token (TokenType type, string lexeme, Object *literal, int line);
        string toString ();
};


Token::Token (TokenType type, string lexeme, Object *literal, int line) {
    this -> type = type;
    this -> lexeme = lexeme;
    this -> line = line;
    this -> literal = literal;
}

string Token::toString () {
    return this -> type + " " + this -> lexeme + " " + this -> literal -> toString();
}

# endif