# include "Expr.h"
# include "Token.h"
# include "Expr.h"
# include "Logical.h"
# include "VisitorExprBase.h"

# include <any>
using namespace std;

Logical::Logical (Expr *left, Token op, Expr *right) {
    this ->  left =  left;
    this ->  op =  op;
    this ->  right =  right;
};

/*Binary::~Binary () {
   delete left;
   delete right;
}*/

Expr* Logical::getleft() {
   return this -> left;
}

Token Logical::getop() {
   return this -> op;
}

Expr* Logical::getright() {
   return this -> right;
}

any Logical::accept (VisitorExprBase& visitor) {
   return visitor.visitLogicalExprBase(*this);
}
