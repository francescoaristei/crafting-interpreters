# include "Token.h"
# include "Expr.h"
# include "Unary.h"
# include "VisitorExprBase.h"

# include <any>
using namespace std;


Unary::Unary (Token op, Expr *right) {
    this ->  op =  op;
    this ->  right =  right;
};

/*Unary::~Unary () {
   delete right;
}*/

Token Unary::getop() {
   return this -> op;
}

Expr* Unary::getright() {
   return this -> right;
}

any Unary::accept (VisitorExprBase& visitor) {
   return visitor.visitUnaryExprBase(*this);
}