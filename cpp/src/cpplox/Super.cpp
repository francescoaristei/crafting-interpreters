# include "Expr.h"
# include "Super.h"
# include "Token.h"
# include "VisitorExprBase.h"

# include <any>
using namespace std;

Super::Super (Token keyword, Token method) {
    this -> keyword = keyword;
    this -> method = method;
};

/*Grouping::~Grouping () {
   delete expression;
}*/

Token Super::getkeyword () {
    return this -> keyword;
}

Token Super::getmethod () {
    return this -> method;
}


any Super::accept (VisitorExprBase& visitor) {
   return visitor.visitSuperExprBase(*this);
}