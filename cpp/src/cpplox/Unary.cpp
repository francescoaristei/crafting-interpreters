# include "Token.h"
# include "Expr.h"
# include "Unary.h"
# include "VisitorExprBase.h"

# include <any>
using namespace std;


Unary::Unary (Token *op, Expr *right) {
    this ->  op =  op;
    this ->  right =  right;
};

/*Unary::~Unary () {
   delete right;
}

Unary& Unary::operator= (const Unary& other) {
   if (this == &other) {
      return *this;
   }

   op = other.op;
   delete right;
   right = nullptr;
   right = other.right->deepcopy();
   return *this;
}

Unary::Unary (const Unary& other) {
   op = other.op;
   right = other.right;
}

Unary* Unary::deepcopy () {
   return new Unary(*this);
}*/

Token* Unary::getop() {
   return this -> op;
}

Expr* Unary::getright() {
   return this -> right;
}

any Unary::accept (VisitorExprBase& visitor) {
   return visitor.visitUnaryExprBase(*this);
}