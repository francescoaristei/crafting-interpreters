# ifndef INTERPRETER_CLASS
# define INTERPRETER_CLASS
# include <string>
# include <map>
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
# include "If.h"
# include "While.h"
# include "Logical.h"
# include "Function.h"
# include "Return.h"
# include "Class.h"
# include "Get.h"
# include "Set.h"
# include "Call.h"
# include "This.h"
# include <iostream>
# include "Environment.h"
//class Environment;

using namespace std;

/* NOTE: Remember to handle memory deletion on the callers of Interpreter */

/* VisitorExpr and VisitorStmt are a class templates, Interpreter extends the cocrete implementation of both with: Object* and void* */
class Interpreter: public VisitorExpr<Object*>, VisitorStmt<void> {
    public:
        Interpreter();
        void visitExpressionStmt (Expression& stmt);
        void visitPrintStmt (Print& stmt);
        void visitVarStmt (Var& stmt);
        void visitBlockStmt (Block& stmt);
        void visitIfStmt (If& stmt);
        void visitWhileStmt (While& stmt);
        void visitFunctionStmt (Function& stmt);
        void visitReturnStmt (Return& stmt);
        void visitClassStmt (Class& stmt);
        Object* visitVariableExpr (Variable& expr);
        Object* visitBinaryExpr (Binary& expr);
        Object* visitGroupingExpr (Grouping& expr);
        Object* visitLiteralExpr (Literal& expr);
        Object* visitUnaryExpr (Unary& expr);
        Object* visitAssignExpr (Assign& expr);
        Object* visitLogicalExpr (Logical& expr);
        Object* visitCallExpr (Call& expr);
        Object* visitGetExpr (Get& expr);
        Object* visitSetExpr (Set& expr);
        Object* visitThisExpr (This& expr);
        void interpret (vector<Stmt*> statements);
        void execute (Stmt* stmt);
        void resolve (Expr *expr, int depth);
        void executeBlock (vector<Stmt*> statements, Environment *environment);
        Environment *globals = new Environment();
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
        class ReturnEx: public runtime_error {
            public:
                ReturnEx (Object *value) : runtime_error("return") {
                    this -> value = value;
                }
                Object* getvalue() {return this -> value;};
            private:
                Object* value;

        };
    private:
        Object* evaluate (Expr* expr);
        bool isTruthy(Object *object);
        bool isEqual(Object *a, Object *b);
        //Environment *environment = new Environment();
        Environment *environment = globals;
        void checkNumberOperand(Token op, Object *operand);
        void checkNumberOperands(Token op, Object *operand1, Object *operand2);
        string stringify(Object *object);
        map<Expr*, int> locals;
        Object* lookUpVariable(Token name, Expr *expr);
};

# endif