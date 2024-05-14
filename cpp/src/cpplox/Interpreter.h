# ifndef INTERPRETER
# define INTERPRETER
# include <string>
# include "Visitor.h"
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
# include <iostream>

using namespace std;

/* NOTE: Remember to handle memory deletion on the callers of Interpreter */

/* Visitor is a class template, Interpreter extends the concrete implementation of Visitor with string: Visitor<string> */
template <typename R>
class Interpreter: public Visitor<Object*> {
    public:
        Object* visitBinaryExpr (Binary<R>& expr);
        Object* visitGroupingExpr (Grouping<R>& expr);
        Object* visitLiteralExpr (Literal<R>& expr);
        Object* visitUnaryExpr (Unary<R>& expr);
        void interpret (Expr<R>* expression);
        class RuntimeError: public runtime_error {
            public:
                RuntimeError(Token token, const string& message) { 
                    this -> token = token;
                    this -> message = message;
                    }
                string getMessage () {return this -> message;}
                Token getToken () {return this -> token};
            private:
                string message;
                Token token;
        };
    private:
        Object* evaluate (Expr<R>* expr);
        bool isTruthy(Object *object);
        bool isEqual(Object *a, Object *b);
        void checkNumberOperand(Token op, Object *operand);
        void checkNumberOperands(Token op, Object *operand1, Object *operand2);
        string stringify(Object *object);
};

template <typename R>
void Interpreter<R>::interpret (Expr<R> *expression) {
    try {
        Object *value = evaluate(expression);
        cout << stringify(value);
    } catch (Interpreter<R>::RuntimeError error) {
        Lox::runtimeError(error);
    }
}

template <typename R>
Object* Interpreter<R>::visitBinaryExpr (Binary<R>& expr) {
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
            if (Double* d1 = dynamic_cast<Double*>(object) && Double* d2 = dynamic_cast<Double*>(object)) {
                return new Double(d1 -> getValue() + d2 -> getValue());
            }
            if (String* s1 = dynamic_cast<String*>(object) && String* s2 = dynamic_cast<String*>(object)) {
                return new String(s1 -> getValue() + s2 -> getValue());
            }
            throw new Interpreter<R>::RuntimeError(expr.getop(), "Operands must be two numbers or two strings.");
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

template <typename R>
Object* Interpreter<R>::visitGroupingExpr (Grouping<R>& expr) {
    return evaluate(expr.getExpression());
}

template <typename R>
Object* Interpreter<R>::visitLiteralExpr (Literal<R>& expr) {
    if (expr.getvalue() == NULL) return new String("nil");
    return expr.getvalue();
}

/* post order traversal of the unary expression syntax tree */
template <typename R>
Object* Interpreter<R>::visitUnaryExpr (Unary<R>& expr) {
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

template <typename R>
bool Interpreter<R>::isEqual (Object *a, Object *b) {
    if (a == NULL && b == NULL) return true;
    if (a == NULL) return false;
    /* check if point to same memory region for equality */
    return a == b;
}

template <typename R>
bool Interpreter<R>::isTruthy (Object *object) {
    if (object == NULL) return false;
    if (Boolean* b = dynamic_cast<Boolean*>(object)) return b -> getValue();
}

template <typename R>
Object* Interpreter<R>::evaluate (Expr<R>* expr) {
    return expr -> accept(*this);
}

template <typename R>
void Interpreter<R>::checkNumberOperand (Token op, Object *operand) {
    if (Double* d = dynamic_cast<Double*>(operand)) return;
    throw new Interpreter<R>::RuntimeError(op, "Operand must be a number.");
}

template <typename R>
void Interpreter<R>::checkNumberOperands (Token op, Object *operand1, Object *operand2) {
    if (Double* d1 = dynamic_cast<Double*>(operand1) && Double* d2 = dynamic_cast<Double*>(operand2)) return;
    throw new Interpreter<R>::RuntimeError(op, "Operands must be numbers.");
}

/* CHECK AGAIN IF IT IS CORRECT (chapter Hooking Up the Interpreter)*/
template <typename R>
string Interpreter<R>::stringify (Object *object) {
    if (object == NULL) return "nil";
    return object -> toString();
}

# endif