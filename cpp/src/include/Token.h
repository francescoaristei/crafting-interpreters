
# ifndef TOKEN_CLASS
# define TOKEN_CLASS
# include "TokenType.h"
# include <stdio.h>
# include "Object.h"

using namespace std;


class Token {
    public:
        Token (TokenType type, string lexeme, Object *literal, int line);
        /* default empty constructor if is not defined */
        Token () = default;
        //~Token();
        string toString ();
        string getLexeme();
        TokenType getType();
        int getLine();
        Object* getLiteral();
    private:
        TokenType type;
        string lexeme;
        int line;
        Object *literal;
};

# endif