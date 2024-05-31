# include "Expr.h"
# include "Get.h"
# include "Token.h"
# include "VisitorExprBase.h"

# include <any>
using namespace std;

Get::Get (Expr *object, Token name) {
    this ->  object =  object;
    this -> name = name;
};

/*Grouping::~Grouping () {
   delete expression;
}*/

Expr* Get::getobject() {
   return this -> object;
}

Token Get::getname () {
    return this -> name;
}

any Get::accept (VisitorExprBase& visitor) {
   return visitor.visitGetExprBase(*this);
}