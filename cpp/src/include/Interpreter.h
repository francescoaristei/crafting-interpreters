# ifndef INTERPRETER
# define INTERPRETER
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
# include <iostream>

using namespace std;

/* NOTE: Remember to handle memory deletion on the callers of Interpreter */

/* VisitorExpr and VisitorStmt are a class templates, Interpreter extends the cocrete implementation of both with: Object* and void* */
class Interpreter: public VisitorExpr<Object*>, VisitorStmt<void> {
    public:
        void visitExpressionStmt (Expression& stmt);
        void visitPrintStmt (Print& stmt);
        Object* visitBinaryExpr (Binary& expr);
        Object* visitGroupingExpr (Grouping& expr);
        Object* visitLiteralExpr (Literal& expr);
        Object* visitUnaryExpr (Unary& expr);
        void interpret (vector<Stmt*> statements);
        void execute (Stmt* stmt);
        class RuntimeError: public runtime_error {
            public:
                RuntimeError(Token token, const string& message) 
                    : message(message)
                    , token(token)
                    , runtime_error(message) 
                    {}
                string getMessage () {return this -> message;}
                Token getToken () {return this -> token;}
            private:
                string message;
                Token token;
        };
    private:
        Object* evaluate (Expr* expr);
        bool isTruthy(Object *object);
        bool isEqual(Object *a, Object *b);
        void checkNumberOperand(Token op, Object *operand);
        void checkNumberOperands(Token op, Object *operand1, Object *operand2);
        string stringify(Object *object);
};



# endif