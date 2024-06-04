# ifndef VISITOR_EXPR
# define VISITOR_EXPR
# include "Binary.h"
# include "Grouping.h"
# include "Literal.h"
# include "Unary.h"
# include "VisitorExprBase.h"
# include "Variable.h"
# include "Assign.h"
# include "Logical.h"
# include "Call.h"
# include "Get.h"
# include "Set.h"
# include "This.h"
# include "Super.h"

# include <any>
using namespace std;

template <typename R>
class VisitorExpr : public VisitorExprBase {
   public:
        virtual R visitBinaryExpr (Binary& expr) = 0;
        virtual R visitGroupingExpr (Grouping& expr) = 0;
        virtual R visitLiteralExpr (Literal& expr) = 0;
        virtual R visitUnaryExpr (Unary& expr) = 0;
        virtual R visitVariableExpr (Variable& expr) = 0;
        virtual R visitAssignExpr (Assign& expr) = 0;
        virtual R visitLogicalExpr (Logical& expr) = 0;
        virtual R visitCallExpr (Call& expr) = 0;
        virtual R visitGetExpr (Get& expr) = 0;
        virtual R visitSetExpr (Set& expr) = 0;
        virtual R visitThisExpr (This& expr) = 0;
        virtual R visitSuperExpr (Super& expr) = 0;
        
        any visitBinaryExprBase (Binary& expr) override {
            return static_cast<any>(visitBinaryExpr(expr));
        }
        any visitGroupingExprBase (Grouping& expr) override {
            return static_cast<any>(visitGroupingExpr(expr));
        }
        any visitLiteralExprBase (Literal& expr) override {
            return static_cast<any>(visitLiteralExpr(expr));
        }
        any visitUnaryExprBase (Unary& expr) override {
            return static_cast<any>(visitUnaryExpr(expr));
        }
        any visitVariableExprBase (Variable& expr) override {
            return static_cast<any>(visitVariableExpr(expr));
        }
        any visitAssignExprBase (Assign& expr) override {
            return static_cast<any>(visitAssignExpr(expr));
        }
        any visitLogicalExprBase (Logical& expr) override {
            return static_cast<any>(visitLogicalExpr(expr));
        }
        any visitCallExprBase (Call& expr) override {
            return static_cast<any>(visitCallExpr(expr));
        }
        any visitGetExprBase (Get& expr) override {
            return static_cast<any>(visitGetExpr(expr));
        }
        any visitSetExprBase (Set& expr) override {
            return static_cast<any>(visitSetExpr(expr));
        }
        any visitThisExprBase (This& expr) override {
            return static_cast<any>(visitThisExpr(expr));
        }
        any visitSuperExprBase (Super& expr) override {
            return static_cast<any>(visitSuperExpr(expr));
        }
};


template <>
class VisitorExpr<void>: public VisitorExprBase {
    public:
        virtual void visitBinaryExpr (Binary& expr) = 0;
        virtual void visitGroupingExpr (Grouping& expr) = 0;
        virtual void visitLiteralExpr (Literal& expr) = 0;
        virtual void visitUnaryExpr (Unary& expr) = 0;
        virtual void visitVariableExpr (Variable& expr) = 0;
        virtual void visitAssignExpr (Assign& expr) = 0;
        virtual void visitLogicalExpr (Logical& expr) = 0;
        virtual void visitCallExpr (Call& expr) = 0;
        virtual void visitGetExpr (Get& expr) = 0;
        virtual void visitSetExpr (Set& expr) = 0;
        virtual void visitThisExpr (This& expr) = 0;
        virtual void visitSuperExpr (Super& expr) = 0;

        any visitBinaryExprBase (Binary& expr) override {
            visitBinaryExpr(expr);
            return {};
        }

        any visitGroupingExprBase (Grouping& expr) override {
            visitGroupingExpr(expr);
            return {};
        }
        any visitLiteralExprBase (Literal& expr) override {
            visitLiteralExpr(expr);
            return {};
        }
        any visitUnaryExprBase (Unary& expr) override {
            visitUnaryExpr(expr);
            return {};
        }
        any visitVariableExprBase (Variable& expr) override {
            visitVariableExpr(expr);
            return {};
        }
        any visitAssignExprBase (Assign& expr) override {
            visitAssignExpr(expr);
            return {};
        }
        any visitLogicalExprBase (Logical& expr) override {
            visitLogicalExpr(expr);
            return {};
        }
        any visitCallExprBase (Call& expr) override {
            visitCallExpr(expr);
            return {};
        }

        any visitGetExprBase (Get& expr) override {
            visitGetExpr(expr);
            return {};
        }
        any visitSetExprBase (Set& expr) override {
            visitSetExpr(expr);
            return {};
        }

        any visitThisExprBase (This& expr) override {
            visitThisExpr(expr);
            return {};
        }
        any visitSuperExprBase (Super& expr) override {
            visitSuperExpr(expr);
            return {};
        }

};

# endif
