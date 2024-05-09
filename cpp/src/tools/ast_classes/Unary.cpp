# include "Unary.h"
# include "Token.h"
# include "Expr.h"

Unary::Unary (Token op, Expr right) {
    this ->  op =  op;
    this ->  right =  right;
};