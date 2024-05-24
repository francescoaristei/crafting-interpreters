# ifndef VISITOR_STMT
# define VISITOR_STMT
# include "Print.h"
# include "Expression.h"
# include "Var.h"
# include "VisitorStmtBase.h"
# include "Block.h"
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
};


template <>
class VisitorStmt<void>: public VisitorStmtBase {
    public:
        virtual void visitPrintStmt (Print& stmt) = 0;
        virtual void visitExpressionStmt (Expression& stmt) = 0;
        virtual void visitVarStmt (Var& stmt) = 0;
        virtual void visitBlockStmt (Block& stmt) = 0;

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
};

# endif
