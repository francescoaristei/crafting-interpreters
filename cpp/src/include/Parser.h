# ifndef PARSER_CLASS
# define PARSER_CLASS
# include <vector>
# include "Token.h"
# include "Expr.h"
# include "Binary.h"
# include "TokenType.h"
# include "Grouping.h"
# include "Unary.h"
# include "Literal.h"
# include "Boolean.h"
# include "Lox.h"
# include "Stmt.h"
# include "Print.h"
# include <iostream>

using namespace std;

class Parser {
    public:
        Parser(vector<Token> tokens);
        vector<Stmt*> parse();
    private:
        class ParseError: public runtime_error {
            public:
                ParseError(const string& message) : runtime_error(message){}
        };
        vector<Token> tokens;
        int current = 0;
        Stmt* statement();
        Stmt* printStatement();
        Stmt* expressionStatement();
        Stmt* declaration();
        Stmt* varDeclaration();
        vector<Stmt*> block ();
        Expr* assignment ();
        Expr* expression();
        Expr* equality();
        Expr* comparison();
        Expr* term();
        Expr* factor();
        Expr* unary();
        Expr* primary();
        Token consume(TokenType type, const string& message);
        ParseError error(Token token, const string& message);
        void synchronize();
        bool match(vector<TokenType> types);
        bool check(TokenType type);
        Token advance();
        bool isAtEnd();
        Token peek();
        Token previous();
};

# endif