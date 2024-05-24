# include "Token.h"
# include "Expr.h"
# include "Assign.h"
# include "VisitorExprBase.h"

# include <any>
using namespace std;

Assign::Assign (Token name, Expr *value) {
    this ->  name =  name;
    this ->  value =  value;
};

/*Assign::~Assign () {
   delete value;
}*/

Token Assign::getname() {
   return this -> name;
}

Expr* Assign::getvalue() {
   return this -> value;
}

any Assign::accept (VisitorExprBase& visitor) {
   return visitor.visitAssignExprBase(*this);
}
