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
}

Binary& Binary::operator= (const Binary& other) {
   if (&other == this)
      return *this;
   
   op = other.op;
   delete left;
   delete right;
   left = nullptr;
   right = nullptr;
   left = other.left->deepcopy();
   right = other.right->deepcopy();

   return *this;
}

Binary::Binary (const Binary& other) {
   op = other.op;
   left = other.left;
   right = other.right;
}


Binary* Binary::deepcopy () {
   return new Binary(*this);
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
