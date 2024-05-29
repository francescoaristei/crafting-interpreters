# include "Expr.h"
# include "Token.h"
# include "Call.h"
# include <vector>
# include "VisitorExprBase.h"

# include <any>
using namespace std;

Call::Call (Expr *callee, Token paren, vector<Expr*> arguments) {
    this ->  callee =  callee;
    this ->  paren =  paren;
    this ->  arguments =  arguments;
};

/*Binary::~Binary () {
   delete left;
   delete right;
}*/

Expr* Call::getcallee() {
   return this -> callee;
}

Token Call::getparen() {
   return this -> paren;
}

vector<Expr*> Call::getarguments() {
   return this -> arguments;
}

any Call::accept (VisitorExprBase& visitor) {
   return visitor.visitCallExprBase(*this);
}
