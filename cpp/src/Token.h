
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

# endif