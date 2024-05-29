# ifndef VISITOR_STMT
# define VISITOR_STMT
# include "Print.h"
# include "Expression.h"
# include "Var.h"
# include "VisitorStmtBase.h"
# include "Block.h"
# include "If.h"
# include "While.h"
# include "Function.h"
# include "Return.h"
# include <any>
# include <type_traits>
using namespace std;

template <typename R>
class VisitorStmt: public VisitorStmtBase {
   public:
        virtual R visitExpressionStmt (Expression& stmt) = 0;
        virtual R visitPrintStmt (Print& stmt) = 0;
        virtual R visitVarStmt (Var& stmt) = 0;
        virtual R visitBlockStmt (Block& stmt) = 0;
        virtual R visitIfStmt (If& stmt) = 0;
        virtual R visitWhileStmt (While& stmt) = 0;
        virtual R visitFunctionStmt (Function& stmt) = 0;
        virtual R visitReturnStmt (Return& stmt) = 0;

        any visitExpressionStmtBase (Expression& stmt) override {
            return static_cast<any>(visitExpressionStmt(stmt));
        }
        
        any visitPrintStmtBase (Print& stmt) override {
            return static_cast<any>(visitPrintStmt(stmt));
        }

        any visitVarStmtBase (Var& stmt) override {
            return static_cast<any>(visitVarStmt(stmt));
        }

        any visitBlockStmtBase (Block& stmt) override {
            return static_cast<any>(visitBlockStmt(stmt));
        }

        any visitIfStmtBase (If& stmt) override {
            return static_cast<any>(visitIfStmt(stmt));
        }

        any visitWhileStmtBase (While& stmt) override {
            return static_cast<any>(visitWhileStmt(stmt));
        }

        any visitFunctionStmtBase (Function& stmt) override {
            return static_cast<any>(visitFunctionStmt(stmt));
        }
        any visitReturnStmtBase (Return& stmt) override {
            return static_cast<any>(visitReturnStmt(stmt));
        }
};


template <>
class VisitorStmt<void>: public VisitorStmtBase {
    public:
        virtual void visitPrintStmt (Print& stmt) = 0;
        virtual void visitExpressionStmt (Expression& stmt) = 0;
        virtual void visitVarStmt (Var& stmt) = 0;
        virtual void visitBlockStmt (Block& stmt) = 0;
        virtual void visitIfStmt (If& stmt) = 0;
        virtual void visitWhileStmt (While& stmt) = 0;
        virtual void visitFunctionStmt (Function& stmt) = 0;
        virtual void visitReturnStmt (Return& stmt) = 0;

        any visitPrintStmtBase (Print& stmt) override {
            visitPrintStmt(stmt);
            return {};
        }

        any visitExpressionStmtBase (Expression& stmt) {
            visitExpressionStmt(stmt);
            return {};
        }

        any visitVarStmtBase (Var& stmt) {
            visitVarStmt(stmt);
            return {};
        }

        any visitBlockStmtBase (Block& stmt) {
            visitBlockStmt(stmt);
            return {};
        }

        any visitIfStmtBase (If& stmt) {
            visitIfStmt(stmt);
            return {};
        }

        any visitWhileStmtBase (While& stmt) {
            visitWhileStmt(stmt);
            return {};
        }

        any visitFunctionStmtBase (Function& stmt) {
            visitFunctionStmt(stmt);
            return {};
        }

        any visitReturnStmtBase (Return& stmt) {
            visitReturnStmt(stmt);
            return {};
        }
};

# endif
