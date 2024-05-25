# ifndef INTERPRETER_CLASS
# define INTERPRETER_CLASS
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
# include "Var.h"
# include "Variable.h"
# include "Block.h"
# include <iostream>
# include "Environment.h"
//class Environment;

using namespace std;

/* NOTE: Remember to handle memory deletion on the callers of Interpreter */

/* VisitorExpr and VisitorStmt are a class templates, Interpreter extends the cocrete implementation of both with: Object* and void* */
class Interpreter: public VisitorExpr<Object*>, VisitorStmt<void> {
    public:
        void visitExpressionStmt (Expression& stmt);
        void visitPrintStmt (Print& stmt);
        void visitVarStmt (Var& stmt);
        void visitBlockStmt (Block& stmt);
        Object* visitVariableExpr (Variable& expr);
        Object* visitBinaryExpr (Binary& expr);
        Object* visitGroupingExpr (Grouping& expr);
        Object* visitLiteralExpr (Literal& expr);
        Object* visitUnaryExpr (Unary& expr);
        Object* visitAssignExpr (Assign& expr);
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
        Environment *environment = new Environment();
        void checkNumberOperand(Token op, Object *operand);
        void checkNumberOperands(Token op, Object *operand1, Object *operand2);
        string stringify(Object *object);
        void executeBlock (vector<Stmt*> statements, Environment *environment);
};

# endif