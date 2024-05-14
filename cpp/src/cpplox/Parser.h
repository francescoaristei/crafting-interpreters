
# ifndef PARSER
# define PARSER
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

# include <iostream>

using namespace std;

template <typename R>
class Parser {
    public:
        Parser(vector<Token> tokens);
        Expr<R>* parse();
    private:
        class ParseError: public runtime_error {
            public:
                ParseError(const string& message) : runtime_error(message){}
        };
        vector<Token> tokens;
        int current = 0;
        Expr<R>* expression();
        Expr<R>* equality();
        Expr<R>* comparison();
        Expr<R>* term();
        Expr<R>* factor();
        Expr<R>* unary();
        Expr<R>* primary();
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

template <typename R>
Token Parser<R>::peek () {
    return tokens[current];
}

template <typename R>
Token Parser<R>::previous () {
    return tokens[current - 1];
}

template <typename R>
bool Parser<R>::isAtEnd () {
    return peek().getType() == EOF;
}

template<typename R>
bool Parser<R>::check (TokenType type) {
    if (isAtEnd()) return false;
    return peek().getType() == type;
}

template <typename R>
Token Parser<R>::advance () {
    if (!isAtEnd()) current++;
    return previous();
}

template<typename R>
bool Parser<R>::match (vector<TokenType> types) {
    for (vector<TokenType>::iterator itr = types.begin(); itr != types.end(); ++itr) {
        if (check(*itr)) {
            advance();
            return true;
        }
    }

    return false;
}

/* ADJUST to return POINTER? */
template <typename R>
typename Parser<R>::ParseError Parser<R>::error (Token token, const string& message) {
    Lox::error(token, message);
    return Parser<R>::ParseError(message);
}

template <typename R>
void Parser<R>::synchronize () {
    advance();

    while (!isAtEnd()) {
        if (previous().type == SEMICOLON) return;

        switch (peek().type) {
            case CLASS:
            case FUN:
            case VAR:
            case FOR:
            case IF:
            case WHILE:
            case PRINT:
            case RETURN:
                return;
        }
        advance();
    }
}

template <typename R>
Token Parser<R>::consume (TokenType type, const string& message) {
    if (check(type)) return advance();

    throw error(peek(), message);
}


/* primary --> NUMBER | STRING | "true" | "false" | "nil" | "("expression")" */
template <typename R>
Expr<R>* Parser<R>::primary() {
    if (match(vector<TokenType>{FALSE})) return new Literal<R>(new Boolean(false));
    if (match(vector<TokenType>{TRUE})) return new Literal<R>(new Boolean(true));
    if (match(vector<TokenType>{NIL})) return new Literal<R>(NULL);

    if (match(vector<TokenType>{NUMBER, STRING})) {
        return new Literal<R>(previous().getLiteral());
    }

    if (match(vector<TokenType>{LEFT_PAREN})) {
        Expr<R> *expr = expression();
        consume(RIGHT_PAREN, "Expect ')' after expression.");
        return new Grouping<R>(expr);
    }

    throw error(peek(), "Expect expression.");
}

/* unary --> ("!" | "-") unary | primary */
template <typename R>
Expr<R>* Parser<R>::unary () {
    if (match(vector<TokenType>{BANG, MINUS})) {
        Token op = previous();
        Expr<R> *right = unary();
        return new Unary<R>(op, right);
    }

    return primary();
}

template <typename R>
Expr<R>* Parser<R>::factor () {
    Expr<R> *expr = unary();

    while (match(vector<TokenType>{SLASH, STAR})) {
        Token op = previous();
        Expr<R> *right = unary();
        expr = new Binary<R>(expr, op, right);
    }

    return expr;
}

template <typename R>
Expr<R>* Parser<R>::term () {
    Expr<R> *expr = factor();
    while (match(vector<TokenType>{MINUS, PLUS})) {
        Token op = previous();
        Expr<R> *right = factor();
        expr = new Binary<R>(expr, op, right);
    }

    return expr;
}


/* comparison --> term ( ( ">" | ">=" | "<=" | "<=" ) term)* */
template <typename R>
Expr<R>* Parser<R>::comparison () {
    Expr<R> *expr = term();
    while (match(vector<TokenType>{GREATER, GREATER_EQUAL, LESS, LESS_EQUAL})) {
        Token op = previous();
        Expr<R> *right = term();
        expr = new Binary<R>(expr, op, right);
    }
    return expr;
}

/* equality --> comparison (("!=" | "==") comparison)* */
template <typename R>
Expr<R>* Parser<R>::equality () {
    Expr<R> *expr = comparison();
    while (match(vector<TokenType>{BANG_EQUAL, EQUAL_EQUAL})) {
        cout << "ENTERED";
        Token op = previous();
        Expr<R> *right = comparison();
        /* recursively nests binary expressions made by: comparison (!= OR ==) comparison */
        expr = new Binary<R>(expr, op, right);
    }

    return expr;
}

/* expression --> equality */
template <typename R>
Expr<R>* Parser<R>::expression () {
    return equality();
}

template <typename R>
Expr<R>* Parser<R>::parse () {
    try {
        return expression();
    } catch (ParseError error) {
        return NULL;
    }
}

template <typename R>
Parser<R>::Parser (vector<Token> tokens) {
    this -> tokens = tokens;
}

# endif