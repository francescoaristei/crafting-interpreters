# include "Expr.h"
# include "Set.h"
# include "Token.h"
# include "VisitorExprBase.h"

# include <any>
using namespace std;

Set::Set (Expr *object, Token name, Expr *value) {
    this ->  object =  object;
    this -> value = value;
    this -> name = name;
};

/*Grouping::~Grouping () {
   delete expression;
}*/

Expr* Set::getobject() {
   return this -> object;
}

Token Set::getname () {
    return this -> name;
}

Expr* Set::getvalue () {
    return this -> value;
}

any Set::accept (VisitorExprBase& visitor) {
   return visitor.visitSetExprBase(*this);
}