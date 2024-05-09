# include "Binary.h"
# include "Expr.h"
# include "Token.h"
# include "Expr.h"

Binary::Binary (Expr left, Token op, Expr right) {
    this ->  left =  left;
    this ->  op =  op;
    this ->  right =  right;
};