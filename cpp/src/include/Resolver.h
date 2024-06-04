# ifndef RESOLVER_CLASS
# define RESOLVER_CLASS

# include <vector>
# include <map>
# include <stack>
# include <string>
# include "VisitorExpr.h"
# include "VisitorStmt.h"
# include "Interpreter.h"
# include "Variable.h"
# include "Block.h"
# include "Stmt.h"
# include "Expr.h"
# include "Var.h"
# include "Token.h"
# include "Assign.h"
# include "Function.h"
# include "Expression.h"
# include "If.h"
# include "Print.h"
# include "Return.h"
# include "While.h"
# include "Binary.h"
# include "Call.h"
# include "Grouping.h"
# include "Literal.h"
# include "Logical.h"
# include "Unary.h"
# include "Class.h"
# include "Get.h"
# include "Set.h"
# include "This.h"
# include "Super.h"

class Resolver: public VisitorExpr<void>, VisitorStmt<void> {
    public:
        Resolver (Interpreter interpreter);
        void visitBlockStmt (Block& stmt);
        void visitVarStmt (Var& stmt);
        void visitFunctionStmt (Function& stmt);
        void visitExpressionStmt (Expression& stmt);
        void visitIfStmt (If& stmt);
        void visitPrintStmt (Print& stmt);
        void visitReturnStmt (Return& stmt);
        void visitWhileStmt (While& stmt);
        void visitClassStmt (Class& stmt);
        void visitVariableExpr (Variable& expr);
        void visitAssignExpr (Assign& expr);
        void visitBinaryExpr (Binary& expr);
        void visitCallExpr (Call& expr);
        void visitGroupingExpr (Grouping& expr);
        void visitLiteralExpr (Literal& expr);
        void visitLogicalExpr (Logical& expr);
        void visitUnaryExpr (Unary& expr);
        void visitGetExpr (Get& expr);
        void visitSetExpr (Set& expr);
        void visitThisExpr (This& expr);
        void visitSuperExpr (Super& expr);
        void resolve (vector<Stmt*> statements);

    private:
        enum FunctionType {NONE_F, FUNCTION, METHOD, INITIALIZER};
        enum ClassType {NONE_C, CLASS, SUBCLASS};
        stack<map<string, bool>> scopes;
        Interpreter interpreter;
        void resolve (Stmt *stmt);
        void resolve (Expr *expr);
        void beginScope ();
        void endScope ();
        void declare (Token name);
        void define (Token name);
        void resolveLocal (Expr *expr, Token name);
        void resolveFunction (Function *function, FunctionType type);
        FunctionType currentFunction = FunctionType::NONE_F;
        ClassType currentClass = ClassType::NONE_C;

};

# endif