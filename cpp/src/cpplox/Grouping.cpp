# include "Expr.h"
# include "Grouping.h"
# include "VisitorExprBase.h"

# include <any>
using namespace std;

Grouping::Grouping (Expr *expression) {
    this ->  expression =  expression;
};

Grouping::~Grouping () {
   delete expression;
}

Grouping& Grouping::operator= (const Grouping& other) {
   if (this == &other) {
      return *this;
   }

   delete expression;
   expression = nullptr;
   expression = other.expression->deepcopy();
   return *this;
}

Grouping::Grouping (const Grouping& other) {
   expression = expression;
}

Grouping* Grouping::deepcopy () {
   return new Grouping(*this);
}

Expr* Grouping::getexpression() {
   return this -> expression;
}

any Grouping::accept (VisitorExprBase& visitor) {
   return visitor.visitGroupingExprBase(*this);
}