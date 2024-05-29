# include "Expr.h"
# include "Stmt.h"
# include "Return.h"
# include "Token.h"
# include "VisitorStmtBase.h"

# include <any>
using namespace std;

Return::Return (Token keyword, Expr *value) {
    this ->  value =  value;
    this -> keyword = keyword;
};

/*Print::~Print () {
   delete expression;
}*/

Expr* Return::getvalue() {
   return this -> value;
}

Token Return::getkeyword () {
    return this -> keyword;
}

any Return::accept (VisitorStmtBase& visitor) {
   return visitor.visitReturnStmtBase(*this);
}