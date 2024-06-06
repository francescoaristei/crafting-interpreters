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
# include "Var.h"
# include "Variable.h"
# include "Block.h"
# include "If.h"
# include "While.h"
# include "Call.h"
# include "Return.h"
# include "Class.h"
# include "Get.h"
# include "Set.h"
# include "This.h"
# include "Super.h"
# include <iostream>

using namespace std;


Token* Parser::peek () {
    return tokens[current];
}

Token* Parser::previous () {
    return tokens[current - 1];
}

bool Parser::isAtEnd () {
    return peek()->getType() == EOFF;
}

bool Parser::check (TokenType type) {
    if (isAtEnd()) return false;
    return peek()->getType() == type;
}

Token* Parser::advance () {
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
typename Parser::ParseError Parser::error (Token *token, const string& message) {
    Lox::error(token, message);
    return Parser::ParseError(message);
}

void Parser::synchronize () {
    advance();

    while (!isAtEnd()) {
        if (previous()->getType() == SEMICOLON) return;

        switch (peek()->getType()) {
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

Token* Parser::consume (TokenType type, const string& message) {
    if (check(type)) return advance();

    throw error(peek(), message);
}


/* primary --> NUMBER | STRING | "true" | "false" | "nil" | "("expression")" */
Expr* Parser::primary() {
    if (match(vector<TokenType>{FALSE})) return new Literal(new Boolean(false));
    if (match(vector<TokenType>{TRUE})) return new Literal(new Boolean(true));
    if (match(vector<TokenType>{NIL})) return new Literal(NULL);

    if (match(vector<TokenType>{NUMBER, STRING})) {
        return new Literal(previous()->getLiteral());
    }

    if (match(vector<TokenType>{SUPER})) {
        Token *keyword = previous();
        consume(DOT, "Expect '.' after 'super'.");
        Token *method = consume(IDENTIFIER,
                "Expect superclass method name.");
        return new Super(keyword, method);
    }

    if (match(vector<TokenType>{IDENTIFIER})) {
        return new Variable(previous());
    }

    if (match(vector<TokenType>{THIS})) {
        return new This(previous());
    }

    if (match(vector<TokenType>{LEFT_PAREN})) {
        Expr *expr = expression();
        consume(RIGHT_PAREN, "Expect ')' after expression.");
        return new Grouping(expr);
    }

    throw error(peek(), "Expect expression.");
}

Expr* Parser::call () {
    Expr *expr = primary();

    while (true) {
        if (match(vector<TokenType>{LEFT_PAREN})) {
            expr = finishCall(expr);
        } else if (match(vector<TokenType>{DOT})) {
            Token *name = consume (IDENTIFIER,
                "Expect property name after '.'.");
            expr = new Get(expr, name);
        } else {
            break;
        }
    }
    return expr;
}

Expr* Parser::finishCall (Expr *callee) {
    vector<Expr*> arguments;

    if (!check(RIGHT_PAREN)) {
        do {
            if (arguments.size() >= 255) {
                error(peek(), "Can't have more than 255 arguments.");
            }
            arguments.push_back(expression());
        } while (match(vector<TokenType>{COMMA}));
    }
    Token *paren = consume(RIGHT_PAREN, "Expect ')' after arguments.");

    return new Call(callee, paren, arguments);
}

/* unary --> ("!" | "-") unary | primary */
Expr* Parser::unary () {
    if (match(vector<TokenType>{BANG, MINUS})) {
        Token *op = previous();
        Expr *right = unary();
        return new Unary(op, right);
    }

    Expr *expr = call();

    return expr;
}

Expr* Parser::factor () {
    Expr *expr = unary();

    while (match(vector<TokenType>{SLASH, STAR})) {
        Token *op = previous();
        Expr *right = unary();
        expr = new Binary(expr, op, right);
    }

    return expr;
}

Expr* Parser::term () {
    Expr *expr = factor();
    while (match(vector<TokenType>{MINUS, PLUS})) {
        Token *op = previous();
        Expr *right = factor();
        expr = new Binary(expr, op, right);
    }

    return expr;
}


/* comparison --> term ( ( ">" | ">=" | "<=" | "<=" ) term)* */
Expr* Parser::comparison () {
    Expr *expr = term();
    while (match(vector<TokenType>{GREATER, GREATER_EQUAL, LESS, LESS_EQUAL})) {
        Token *op = previous();
        Expr *right = term();
        expr = new Binary(expr, op, right);
    }
    return expr;
}

/* equality --> comparison (("!=" | "==") comparison)* */
Expr* Parser::equality () {
    Expr *expr = comparison();
    while (match(vector<TokenType>{BANG_EQUAL, EQUAL_EQUAL})) {
        Token *op = previous();
        Expr *right = comparison();
        /* recursively nests binary expressions made by: comparison (!= OR ==) comparison */
        expr = new Binary(expr, op, right);
    }

    return expr;
}


Expr* Parser::andexpr () {
    Expr *expr = equality();

    while (match(vector<TokenType>{AND})) {
        Token *op = previous();
        Expr *right = equality();
        expr = new Logical(expr, op, right);
    }

    return expr;
}

Expr* Parser::orexpr () {
    Expr *expr = andexpr();
    while (match(vector<TokenType>{OR})) {
        Token *op = previous();
        Expr *right = andexpr();
        expr = new Logical(expr, op, right);
    }

    return expr;
}

Expr* Parser::assignment () {
    Expr* expr = orexpr();

    if (match({EQUAL})) {
        Token *equals = previous();
        Expr *value = assignment();

        if (Variable* v1 = dynamic_cast<Variable*>(expr)) {
            Token *name = dynamic_cast<Variable*>(expr)->getname();
            return new Assign(name, value);
        } else if (Get* g1 = dynamic_cast<Get*>(expr)) {
            Get *get = dynamic_cast<Get*>(expr);
            return new Set(get->getobject(), get->getname(), value);
        }

        error(equals, "Invalid assignment target."); 
    }

    return expr;
}

/* expression --> assignment */
Expr* Parser::expression () {
    //return equality();
    return assignment();
}

vector<Stmt*> Parser::block () {
    vector<Stmt*> statements;

    while (!check(RIGHT_BRACE) && !isAtEnd()) {
        statements.push_back(declaration());
    }

    consume(RIGHT_BRACE, "Expect '}' after block.");
    return statements;
}

Stmt* Parser::statement () {
    if (match(vector<TokenType>{RETURN})) return returnStatement();
    if (match(vector<TokenType>{FOR})) return forStatement();
    if (match(vector<TokenType>{WHILE})) return whileStatement();
    if (match(vector<TokenType>{IF})) return ifStatement();
    if (match(vector<TokenType>{PRINT})) return printStatement();
    if (match(vector<TokenType>{LEFT_BRACE})) return new Block(block()); 

    return expressionStatement();
}

/* implemented from already available syntax */
Stmt* Parser::forStatement () {
    consume(LEFT_PAREN, "Expect '(' after 'for'.");

    Stmt *initializer;
    if (match(vector<TokenType>{SEMICOLON})) {
        initializer = NULL;
    } else if (match(vector<TokenType>{VAR})) {
        initializer = varDeclaration();
    } else {
        initializer = expressionStatement();
    }

    Expr *condition = NULL;
    if (!check(SEMICOLON)) {
        condition = expression();
    }
    consume (SEMICOLON, "Expect ';' after loop condition.");

    Expr *increment = NULL;
    if (!check(RIGHT_PAREN)) {
        increment = expression();
    }
    consume (RIGHT_PAREN, "Expect ')' after for clauses.");

    Stmt *body = statement();

    if (increment != NULL) {
        body = new Block(
            vector<Stmt*>{body, new Expression(increment)}
        );
    }

    if (condition == NULL) condition = new Literal(new Boolean(true));
    body = new While (condition, body);

    if (initializer != NULL) {
        body = new Block(vector<Stmt*>{initializer, body});
    }
    return body;
}

Stmt* Parser::whileStatement () {
    consume(LEFT_PAREN, "Expect '(' after 'while'.");
    Expr *condition = expression();
    consume(RIGHT_PAREN, "Expect ')' after condition.");
    Stmt *body = statement();

    return new While(condition, body);
}

Stmt* Parser::ifStatement () {
    consume(LEFT_PAREN, "Expect '(' after 'if'.");
    Expr *condition = expression();
    consume (RIGHT_PAREN, "Expect ')' after if condition.");

    Stmt *thenBranch = statement();
    Stmt *elseBranch = NULL;
    if (match(vector<TokenType>{ELSE})) {
        elseBranch = statement();
    }

    return new If(condition, thenBranch, elseBranch);
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

Stmt* Parser::returnStatement () {
    Token *keyword = previous();
    Expr* value = NULL;
    if (!check(SEMICOLON)) {
        value = expression();
    }
    consume(SEMICOLON, "Expect ';' after return value");
    return new Return(keyword, value);
}

Stmt* Parser::classDeclaration () {
    Token *name = consume(IDENTIFIER, "Expect class name.");

    Variable *superclass = NULL;
    if (match(vector<TokenType>{LESS})) {
        consume(IDENTIFIER, "Expect superclass name.");
        superclass = new Variable(previous());
    }

    consume(LEFT_BRACE, "Expect '{' before class body.");

    vector<Stmt*> methods;
    while (!check(RIGHT_BRACE) && !isAtEnd()) {
        Stmt *stmt = function("method");
        methods.push_back(stmt);
    }

    consume(RIGHT_BRACE, "Expect '}' after class body");

    return new Class(name, superclass, methods);
}

Stmt* Parser::varDeclaration () {
    Token *name = consume(IDENTIFIER, "Expect variable name.");

    Expr* initializer = NULL;
    if (match(vector<TokenType>{EQUAL})) {
        initializer = expression();
    }

    consume(SEMICOLON, "Expect ';' after variable declaration.");

    return new Var(name, initializer);
}

Stmt* Parser::function (string kind) {
    Token *name = consume(IDENTIFIER, "Expect " + kind + " name.");
    consume(LEFT_PAREN, "Expect '(' after " + kind + " name.");
    vector<Token*> parameters;
    if (!check(RIGHT_PAREN)) {
        do {
            if (parameters.size() >= 255) {
                error(peek(), "Can't have more than 255 parameters.");
            }
            parameters.push_back(consume(IDENTIFIER, "Expect parameter name.")); 
        } while (match(vector<TokenType>{COMMA}));
    }

    consume(RIGHT_PAREN, "Expect ')' after parameters.");

    consume(LEFT_BRACE, "Expect '{' before " + kind + " body.");
    vector<Stmt*> body = block();
    return new Function(name, parameters, body);
}

Stmt* Parser::declaration () {

    try {
        if (match(vector<TokenType>{CLASS})) {
            return classDeclaration();
        }
        if (match(vector<TokenType>{FUN})) {
            return function("function");
        }
        if (match(vector<TokenType>{VAR})) {
            return varDeclaration();
        }

        return statement();
    } catch (ParseError error) {
        synchronize();
        return NULL;
    }
}

vector<Stmt*> Parser::parse () {
    try {
        vector<Stmt*> statements;
        while (!isAtEnd()) {
            statements.push_back(declaration());
        }
        return statements;
    } catch (ParseError error) {
        /* empty vector */
        return {};
    }
}

Parser::Parser (vector<Token*> tokens) {
    this -> tokens = tokens;
}
