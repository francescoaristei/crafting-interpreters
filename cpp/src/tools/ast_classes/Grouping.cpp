# include "Grouping.h"
# include "Expr.h"
# include "Visitor.h"

Grouping::Grouping (Expr expression) {
    this ->  expression =  expression;

};
Expr Grouping::getexpression() {
   return this -> expression;
}

template <typename R>
R Grouping::accept (Visitor<R>& visitor) {
   return visitor.visitGroupingExpr(this);
}
