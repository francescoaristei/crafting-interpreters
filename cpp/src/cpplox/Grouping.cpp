# include "Expr.h"
# include "Grouping.h"
# include "VisitorExprBase.h"

# include <any>
using namespace std;

Grouping::Grouping (Expr *expression) {
    this ->  expression =  expression;
};

/*Grouping::~Grouping () {
   delete expression;
}*/

Expr* Grouping::getexpression() {
   return this -> expression;
}

any Grouping::accept (VisitorExprBase& visitor) {
   return visitor.visitGroupingExprBase(*this);
}