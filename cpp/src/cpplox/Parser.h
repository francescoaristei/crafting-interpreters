
# ifndef PARSER
# define PARSER
# include <vector>
# include "Token.h"
# include "Expr.h"
# include "Binary.h"
# include "TokenType.h"
# include "Grouping.h"

using namespace std;

template <typename R>
class Parser {
    public:
        Parser(vector<Token> tokens);
        Expr<R> parse();

    private:
        class ParseError: public runtime_error {};
        vector<Token> tokens;
        int current = 0;
        Expr<R> expression();
        Expr<R> equality();
        Expr<R> comparison();
        Expr<R> term();
        Expr<R> factor();
        Expr<R> unary();
        Expr<R> primary();
        Token consume(TokenType type, string message);
        ParseError error(Token toke, string message);
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
    return peek().type == EOF;
}

template<typename R>
bool Parser<R>::check (TokenType type) {
    if (isAtEnd()) return false;
    return peek().type == type;
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

template <typename R>
Parser<R>::ParseError Parser<R>::error (Token token, string message) {
    Lox.error(token, message);
    // TO ADJUST
    return Parser<R>::ParseError();
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
Token Parser<R>::consume (TokenType type, string message) {
    if (check(type)) return advance();

    throw error(peek(), message);
}



/* primary --> NUMBER | STRING | "true" | "false" | "nil" | "("expression")" */
template <typename R>
Expr<R> Parser<R>::primary() {
    // TO ADJUST
    if (match(FALSE)) return Literal(false);
    if (match(TRUE)) return Literal(true);
    if (match(NIL)) return Literal(NULL);

    if (match(NUMBER, STRING)) {
        return Literal(previous().literal);
    }

    if (match(LEFT_PAREN)) {
        Expr<R> expr = expression();
        consume(RIGHT_PAREN, "Expect ')' after expression.");
        return Grouping(expr);
    }

    throw error(peek(), "Expect expression.");
}

/* unary --> ("!" | "-") unary | primary */
template <typename R>
Expr<R> Parser<R>::unary () {
    if (match(BANG, MINUS)) {
        Token operator = previous();
        Expr<R> right = unary();
        // TO ADJUST
        return Unary(operator, right);
    }

    return primary();
}

template <typename R>
Expr<R> Parser<R>::factor () {
    Expr<R> expr = unary();

    while (match(SLASH, STAR)) {
        Token operator = previous();
        Expr<R> right = unary();
        // TO ADJUST
        expr = Binary(expr, operator, right);
    }

    return expr;
}

template <typename R>
Expr<R> Parser<R>::term () {
    Expr<R> expr = factor();
    while (match(MINUS, PLUS)) {
        Token operator = previous();
        Expr<R> right = factor();
        // TO ADJUST
        expr = Binary(expr, operator, right);
    }

    return expr;
}


/* comparison --> term ( ( ">" | ">=" | "<=" | "<=" ) term)* */
template <typename R>
Expr<R> Parser<R>::comparison () {
    Expr<R> expr = term();
    while (match(GREATER, GREATER_EQUAL, LESS, LESS_EQUAL)) {
        Token operator = previous();
        Expr<R> right = term();
        // TO ADJUST
        expr = Binary(expr, operator, right);
    }
    return expr;
}

/* equality --> comparison (("!=" | "==") comparison)* */
template <typename R>
Expr<R> Parser<R>::equality () {
    Expr<R> expr = comparison();
    while (match(BANG_EQUAL, EQUAL_EQUAL)) {
        Token operator = previous();
        Expr<R> right = comparison();
        /* recursively nests binary expressions made by: comparison (!= OR ==) comparison */
        // TO ADJUST
        expr = Binary(expr, operator right);
    }

    return expr;
}

/* expression --> equality */
template <typename R>
Expr<R> Parser<R>::expression () {
    return equality();
}

template <typename R>
Expr<R> Parser<R>::parse () {
    try {
        return expressio();
    } catch (ParseError error) {
        return NULL;
    }
}

template <typename R>
Parser<R>::Parser (vector<Token> tokens) {
    this -> tokens = tokens;
}

# endif