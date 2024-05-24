# include "Expr.h"
# include "Token.h"
# include "Expr.h"
# include "Binary.h"
# include "VisitorExprBase.h"

# include <any>
using namespace std;

Binary::Binary (Expr *left, Token op, Expr *right) {
    this ->  left =  left;
    this ->  op =  op;
    this ->  right =  right;
};

/*Binary::~Binary () {
   delete left;
   delete right;
}*/

Expr* Binary::getleft() {
   return this -> left;
}

Token Binary::getop() {
   return this -> op;
}

Expr* Binary::getright() {
   return this -> right;
}

any Binary::accept (VisitorExprBase& visitor) {
   return visitor.visitBinaryExprBase(*this);
}
