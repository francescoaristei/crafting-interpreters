# include "Expr.h"
# include "This.h"
# include "Token.h"
# include "VisitorExprBase.h"

# include <any>
using namespace std;

This::This (Token name) {
    this -> name = name;
};

/*Grouping::~Grouping () {
   delete expression;
}*/

Token This::getname () {
    return this -> name;
}


any This::accept (VisitorExprBase& visitor) {
   return visitor.visitThisExprBase(*this);
}