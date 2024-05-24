# include <string>
# include "VisitorExpr.h"
# include "VisitorStmt.h"
# include "Expr.h"
# include "Binary.h"
# include "Literal.h"
# include "Unary.h"
# include "Grouping.h"
# include <vector>
# include "TokenType.h"
# include "Double.h"
# include "Boolean.h"
# include "String.h"
# include "Lox.h"
# include "Block.h"
# include <iostream>
# include "Environment.h"
# include "Interpreter.h"
using namespace std;


void Interpreter::execute (Stmt* stmt) {
    stmt -> accept(*this);
}

void Interpreter::interpret (vector<Stmt*> statements) {
    try {
        //Object *value = evaluate(expression);
        //cout << stringify(value);
        for (vector<Stmt*>::iterator itr = statements.begin(); itr != statements.end(); ++itr) {
            execute(*itr);
        }
    } catch (Interpreter::RuntimeError error) {
        /* TO-DO: UNDERSTAND WHY DOES NOT FIND LOX */
        //Lox::runtimeError(error);
    }
}

Object* Interpreter::visitVariableExpr (Variable& expr) {
    return environment -> get(expr.getname());
}

void Interpreter::visitVarStmt (Var& stmt) {
    Object* value = NULL;
    if (stmt.getinitializer() != NULL) {
        value = evaluate(stmt.getinitializer());
    }

    environment -> define(stmt.getToken().getLexeme(), value);
}

void Interpreter::visitExpressionStmt (Expression& stmt) {
    evaluate(stmt.getexpression());
}

void Interpreter::visitPrintStmt (Print& stmt) {
    Object *value = evaluate(stmt.getexpression());
    cout << stringify(value);
}

void Interpreter::visitBlockStmt (Block& stmt) {
    executeBlock(stmt.getstatements(), new Environment(environment));
}

void Interpreter::executeBlock (vector<Stmt*> statements, Environment *environment) {
    Environment *previous = this -> environment;
    this -> environment = environment;
    for (vector<Stmt*>::iterator itr = statements.begin(); itr != statements.end(); ++itr) {
        execute(*itr);
    }
    this -> environment = previous;
}

Object* Interpreter::visitAssignExpr (Assign& expr) {
    Object* value = evaluate(expr.getvalue());
    environment -> assign(expr.getname(), value);
    return value;
}

Object* Interpreter::visitBinaryExpr (Binary& expr) {
    Object *left = evaluate(expr.getleft());
    Object *right = evaluate(expr.getright());

    switch (expr.getop().getType()) {
        case GREATER:
            checkNumberOperands(expr.getop(), left, right);
            return new Boolean(dynamic_cast<Double*>(left) -> getValue() > dynamic_cast<Double*>(right) -> getValue());
        case GREATER_EQUAL:
            checkNumberOperands(expr.getop(), left, right);
            return new Boolean(dynamic_cast<Double*>(left) -> getValue() >= dynamic_cast<Double*>(right) -> getValue());
        case LESS:
            checkNumberOperands(expr.getop(), left, right);
            return new Boolean(dynamic_cast<Double*>(left) -> getValue() < dynamic_cast<Double*>(right) -> getValue());
        case LESS_EQUAL:
            checkNumberOperands(expr.getop(), left, right);
            return new Boolean(dynamic_cast<Double*>(left) -> getValue() <= dynamic_cast<Double*>(right) -> getValue());
        case MINUS:
            checkNumberOperand(expr.getop(), right);
            return new Double(dynamic_cast<Double*>(left) -> getValue() - dynamic_cast<Double*>(right) -> getValue());
        case BANG_EQUAL:
            return new Boolean(!isEqual(left, right));
        case EQUAL_EQUAL:
            return new Boolean(isEqual(left, right));
        case PLUS:
            if (Double* d1 = dynamic_cast<Double*>(left)) {
                if (Double* d2 = dynamic_cast<Double*>(right))
                    return new Double(d1 -> getValue() + d2 -> getValue());
            }
            if (String* s1 = dynamic_cast<String*>(left)) {
                if (String* s2 = dynamic_cast<String*>(right))
                    return new String(s1 -> getValue() + s2 -> getValue());
            }
            throw new Interpreter::RuntimeError(expr.getop(), "Operands must be two numbers or two strings.");
        case SLASH:
            checkNumberOperands(expr.getop(), left, right);
            return new Double(dynamic_cast<Double*>(left) -> getValue() / dynamic_cast<Double*>(right) -> getValue());
        case STAR:
            checkNumberOperands(expr.getop(), left, right);
            return new Double(dynamic_cast<Double*>(left) -> getValue() * dynamic_cast<Double*>(right) -> getValue());
    }

    /* should be unreachable */
    return NULL;
}

Object* Interpreter::visitGroupingExpr (Grouping& expr) {
    return evaluate(expr.getexpression());
}

Object* Interpreter::visitLiteralExpr (Literal& expr) {
    if (expr.getvalue() == NULL) return new String("nil");
    return expr.getvalue();
}

/* post order traversal of the unary expression syntax tree */
Object* Interpreter::visitUnaryExpr (Unary& expr) {
    Object *right = evaluate(expr.getright());
    switch (expr.getop().getType()) {
        case BANG:
            return new Boolean(!isTruthy(right));
        case MINUS:
            return new Double(-(dynamic_cast<Double*>(right) -> getValue()));
    }

    /* unreachable */
    return NULL;
}

bool Interpreter::isEqual (Object *a, Object *b) {
    if (a == NULL && b == NULL) return true;
    if (a == NULL) return false;
    /* check if point to same memory region for equality */
    return a == b;
}

bool Interpreter::isTruthy (Object *object) {
    if (object == NULL) return false;
    if (Boolean* b = dynamic_cast<Boolean*>(object)) return b -> getValue();
}

Object* Interpreter::evaluate (Expr* expr) {
    return any_cast<Object*>(expr -> accept(*this));
}

void Interpreter::checkNumberOperand (Token op, Object *operand) {
    if (Double* d = dynamic_cast<Double*>(operand)) return;
    throw new Interpreter::RuntimeError(op, "Operand must be a number.");
}

void Interpreter::checkNumberOperands (Token op, Object *operand1, Object *operand2) {
    if (Double* d1 = dynamic_cast<Double*>(operand1)) {
        if (Double* d2 = dynamic_cast<Double*>(operand2))
            return;
    }
    throw new Interpreter::RuntimeError(op, "Operands must be numbers.");
}

/* CHECK AGAIN IF IT IS CORRECT (chapter Hooking Up the Interpreter)*/
string Interpreter::stringify (Object *object) {
    if (object == NULL) return "nil";
    return object -> toString();
}