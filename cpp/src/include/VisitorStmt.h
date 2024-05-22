# ifndef VISITOR_STMT
# define VISITOR_STMT
# include "Print.h"
# include "Expression.h"
# include "VisitorStmtBase.h"

# include <any>
# include <type_traits>
using namespace std;

template <typename R>
class VisitorStmt: public VisitorStmtBase {
   public:
        virtual R visitExpressionStmt (Expression& stmt) = 0;
        virtual R visitPrintStmt (Print& stmt) = 0;

        any visitExpressionStmtBase (Expression& stmt) override {
            return static_cast<any>(visitExpressionStmt(stmt));
        }
        
        any visitPrintStmtBase (Print& stmt) override {
            return static_cast<any>(visitPrintStmt(stmt));
        }
};


template <>
class VisitorStmt<void>: public VisitorStmtBase {
    public:
        virtual void visitPrintStmt (Print& stmt) = 0;
        virtual void visitExpressionStmt (Expression& stmt) = 0;

        any visitPrintStmtBase (Print& stmt) override {
            visitPrintStmt(stmt);
            return {};
        }

        any visitExpressionStmtBase (Expression& stmt) {
            visitExpressionStmt(stmt);
            return {};
        }
};

# endif
