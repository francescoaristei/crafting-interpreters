# ifndef VISITOR_EXPR
# define VISITOR_EXPR
# include "Binary.h"
# include "Grouping.h"
# include "Literal.h"
# include "Unary.h"
# include "VisitorExprBase.h"

# include <any>
using namespace std;

template <typename R>
class VisitorExpr : public VisitorExprBase {
   public:
        virtual R visitBinaryExpr (Binary& expr) = 0;
        virtual R visitGroupingExpr (Grouping& expr) = 0;
        virtual R visitLiteralExpr (Literal& expr) = 0;
        virtual R visitUnaryExpr (Unary& expr) = 0;
        
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
};

# endif
