# include "Expr.h"
# include "Stmt.h"
# include "VisitorStmtBase.h"
# include "Var.h"

# include <any>
using namespace std;

Var::Var (Token name, Expr *initializer) {
    this ->  initializer =  initializer;
    this -> name = name;
};

/*Var::~Var () {
    delete initializer;
}*/

Expr* Var::getinitializer() {
   return this -> initializer;
}

Token Var::getToken () {
    return this -> name;
}

any Var::accept (VisitorStmtBase& visitor) {
   return visitor.visitVarStmtBase(*this);
}