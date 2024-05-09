# include "Unary.h"
# include "Token.h"
# include "Expr.h"
# include "Visitor.h"

Unary::Unary (Token op, Expr right) {
    this ->  op =  op;

    this ->  right =  right;

};
Token Unary::getop() {
   return this -> op;
}

Expr Unary::getright() {
   return this -> right;
}

template <typename R>
R Unary::accept (Visitor<R>& visitor) {
   return visitor.visitUnaryExpr(this);
}
