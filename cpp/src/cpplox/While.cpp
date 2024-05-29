# include "Expr.h"
# include "Stmt.h"
# include "While.h"
# include "VisitorStmtBase.h"

# include <any>
using namespace std;

While::While (Expr *expression, Stmt *stmt) {
    this ->  expression =  expression;
    this -> stmt = stmt;
};


Expr* While::getexpression() {
   return this -> expression;
}

Stmt* While::getstmt () {
    return this -> stmt;
}

any While::accept (VisitorStmtBase& visitor) {
   return visitor.visitWhileStmtBase(*this);
}