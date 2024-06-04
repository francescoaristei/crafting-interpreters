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

/*Logical::~Logical () {
   delete left;
   delete right;
}

Logical& Logical::operator= (const Logical& other) {
   if (this == &other) {
      return *this;
   }

   op = other.op;
   delete left;
   left = nullptr;
   left = other.left->deepcopy();
   delete right;
   right = nullptr;
   right = other.right->deepcopy();
   return *this;
}

Logical::Logical (const Logical& other) {
   op = other.op;
   left = other.left;
   right = other.right;
}

Logical* Logical::deepcopy () {
   return new Logical(*this);
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
