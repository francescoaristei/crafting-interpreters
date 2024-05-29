# include "Expr.h"
# include "Stmt.h"
# include "If.h"
# include "VisitorStmtBase.h"

# include <any>
using namespace std;

If::If (Expr *expression, Stmt *thenBranch, Stmt *elseBranch) {
    this ->  expression =  expression;
    this -> thenBranch = thenBranch;
    this -> elseBranch = elseBranch;
};

Expr* If::getexpression() {
   return this -> expression;
}

Stmt* If::getThenBranch () {
    return this -> thenBranch;
}

Stmt* If::getElseBranch () {
    return this -> elseBranch;
}

any If::accept (VisitorStmtBase& visitor) {
   return visitor.visitIfStmtBase(*this);
}