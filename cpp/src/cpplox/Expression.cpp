# include "Expr.h"
# include "Stmt.h"
# include "Expression.h"
# include "VisitorStmtBase.h"

# include <any>
using namespace std;


Expression::Expression (Expr *expression) {
    this ->  expression =  expression;
};

Expression::~Expression () {
   delete expression;
}

Expression& Expression::operator= (const Expression& other) {
   if (this == &other) {
      return *this;
   }

   delete expression;
   expression = nullptr;

   expression = other.expression->deepcopy();
   return *this;
}

Expression::Expression (const Expression& other) {
   expression = other.expression;
}

Expression* Expression::deepcopy () {
   return new Expression(*this);
}

Expr* Expression::getexpression() {
   return this -> expression;
}

any Expression::accept (VisitorStmtBase& visitor) {
   return visitor.visitExpressionStmtBase(*this);
}