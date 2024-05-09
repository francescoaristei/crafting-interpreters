# include "Binary.h"
# include "Expr.h"
# include "Token.h"
# include "Expr.h"
# include "Visitor.h"

Binary::Binary (Expr left, Token op, Expr right) {
    this ->  left =  left;

    this ->  op =  op;

    this ->  right =  right;

};
Expr Binary::getleft() {
   return this -> left;
}

Token Binary::getop() {
   return this -> op;
}

Expr Binary::getright() {
   return this -> right;
}

template <typename R>
R Binary::accept (Visitor<R>& visitor) {
   return visitor.visitBinaryExpr(this);
}
