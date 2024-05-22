# include "Expr.h"
# include "Stmt.h"
# include "Print.h"
# include "VisitorStmtBase.h"

# include <any>
using namespace std;

Print::Print (Expr *expression) {
    this ->  expression =  expression;
};

Expr* Print::getexpression() {
   return this -> expression;
}

any Print::accept (VisitorStmtBase& visitor) {
   return visitor.visitPrintStmtBase(*this);
}