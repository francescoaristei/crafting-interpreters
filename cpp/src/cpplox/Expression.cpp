# include "Expr.h"
# include "Stmt.h"
# include "Expression.h"
# include "VisitorStmtBase.h"

# include <any>
using namespace std;


Expression::Expression (Expr *expression) {
    this ->  expression =  expression;
};

Expr* Expression::getexpression() {
   return this -> expression;
}

any Expression::accept (VisitorStmtBase& visitor) {
   return visitor.visitExpressionStmtBase(*this);
}