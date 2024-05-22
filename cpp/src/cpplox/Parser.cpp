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
# include "Parser.h"
# include <iostream>

using namespace std;


Token Parser::peek () {
    return tokens[current];
}

Token Parser::previous () {
    return tokens[current - 1];
}

bool Parser::isAtEnd () {
    return peek().getType() == EOF;
}

bool Parser::check (TokenType type) {
    if (isAtEnd()) return false;
    return peek().getType() == type;
}

Token Parser::advance () {
    if (!isAtEnd()) current++;
    return previous();
}

bool Parser::match (vector<TokenType> types) {
    for (vector<TokenType>::iterator itr = types.begin(); itr != types.end(); ++itr) {
        if (check(*itr)) {
            advance();
            return true;
        }
    }

    return false;
}

/* ADJUST to return POINTER? */
typename Parser::ParseError Parser::error (Token token, const string& message) {
    Lox::error(token, message);
    return Parser::ParseError(message);
}

void Parser::synchronize () {
    advance();

    while (!isAtEnd()) {
        if (previous().getType() == SEMICOLON) return;

        switch (peek().getType()) {
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

Token Parser::consume (TokenType type, const string& message) {
    if (check(type)) return advance();

    throw error(peek(), message);
}


/* primary --> NUMBER | STRING | "true" | "false" | "nil" | "("expression")" */
Expr* Parser::primary() {
    if (match(vector<TokenType>{FALSE})) return new Literal(new Boolean(false));
    if (match(vector<TokenType>{TRUE})) return new Literal(new Boolean(true));
    if (match(vector<TokenType>{NIL})) return new Literal(NULL);

    if (match(vector<TokenType>{NUMBER, STRING})) {
        return new Literal(previous().getLiteral());
    }

    if (match(vector<TokenType>{LEFT_PAREN})) {
        Expr *expr = expression();
        consume(RIGHT_PAREN, "Expect ')' after expression.");
        return new Grouping(expr);
    }

    throw error(peek(), "Expect expression.");
}

/* unary --> ("!" | "-") unary | primary */
Expr* Parser::unary () {
    if (match(vector<TokenType>{BANG, MINUS})) {
        Token op = previous();
        Expr *right = unary();
        return new Unary(op, right);
    }

    return primary();
}

Expr* Parser::factor () {
    Expr *expr = unary();

    while (match(vector<TokenType>{SLASH, STAR})) {
        Token op = previous();
        Expr *right = unary();
        expr = new Binary(expr, op, right);
    }

    return expr;
}

Expr* Parser::term () {
    Expr *expr = factor();
    while (match(vector<TokenType>{MINUS, PLUS})) {
        Token op = previous();
        Expr *right = factor();
        expr = new Binary(expr, op, right);
    }

    return expr;
}


/* comparison --> term ( ( ">" | ">=" | "<=" | "<=" ) term)* */
Expr* Parser::comparison () {
    Expr *expr = term();
    while (match(vector<TokenType>{GREATER, GREATER_EQUAL, LESS, LESS_EQUAL})) {
        Token op = previous();
        Expr *right = term();
        expr = new Binary(expr, op, right);
    }
    return expr;
}

/* equality --> comparison (("!=" | "==") comparison)* */
Expr* Parser::equality () {
    Expr *expr = comparison();
    while (match(vector<TokenType>{BANG_EQUAL, EQUAL_EQUAL})) {
        Token op = previous();
        Expr *right = comparison();
        /* recursively nests binary expressions made by: comparison (!= OR ==) comparison */
        expr = new Binary(expr, op, right);
    }

    return expr;
}

/* expression --> equality */
Expr* Parser::expression () {
    return equality();
}

/* statement --> exprStmt | printStmt */
Stmt* Parser::statement () {
    if (match(vector<TokenType>{PRINT})) return printStatement();

    return expressionStatement();
}

Stmt* Parser::printStatement () {
    Expr *value = expression();
    consume(SEMICOLON, "Expect ';' after value.");
    return new Print(value);
}

Stmt* Parser::expressionStatement () {
    Expr* expr = expression();
    consume(SEMICOLON, "Expect ';' after expression.");
    return new Expression(expr);
}

vector<Stmt*> Parser::parse () {
    try {
        vector<Stmt*> statements;
        while (!isAtEnd()) {
            statements.push_back(statement());
        }
        return statements;
    } catch (ParseError error) {
        /* empty vector */
        return {};
    }
}

Parser::Parser (vector<Token> tokens) {
    this -> tokens = tokens;
}
