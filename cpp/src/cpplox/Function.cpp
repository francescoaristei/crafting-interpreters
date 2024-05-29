# include "Expr.h"
# include "Stmt.h"
# include "Function.h"
# include <vector>
# include "Token.h"
# include "VisitorStmtBase.h"

# include <any>
using namespace std;

Function::Function (Token name, vector<Token> params, vector<Stmt*> body) {
    this ->  name =  name;
    this -> params = params;
    this -> body = body;
};

/*Print::~Print () {
   delete expression;
}*/

Token Function::getname() {
   return this -> name;
}

vector<Token> Function::getparams () {
    return this -> params;
}

vector<Stmt*> Function::getbody () {
    return this -> body;
}

any Function::accept (VisitorStmtBase& visitor) {
   return visitor.visitFunctionStmtBase(*this);
}