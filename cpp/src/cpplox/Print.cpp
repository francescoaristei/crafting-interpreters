# include "Expr.h"
# include "Stmt.h"
# include "Print.h"
# include "VisitorStmtBase.h"

# include <any>
using namespace std;

Print::Print (Expr *expression) {
    this ->  expression =  expression;
};

Print::~Print () {
   delete expression;
}

Print& Print::operator= (const Print& other) {
   if (this == &other) {
      return *this;
   }

   delete expression;
   expression = nullptr;
   expression = other.expression->deepcopy();
   return *this;
}

Print::Print (const Print& other) {
   expression = other.expression;
}

Print* Print::deepcopy () {
   return new Print(*this);
}

Expr* Print::getexpression() {
   return this -> expression;
}

any Print::accept (VisitorStmtBase& visitor) {
   return visitor.visitPrintStmtBase(*this);
}