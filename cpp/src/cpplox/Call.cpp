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

/*Call::~Call () {
   delete callee;
   for (vector<Expr*>::iterator itr = arguments.begin(); itr != arguments.end(); ++itr) {
        delete *itr;
    }
}

Call& Call::operator= (const Call& other) {
   if (this == &other) {
      return *this;
   }

   paren = other.paren;

   delete callee;
   callee = nullptr;
   callee = other.callee->deepcopy();

   for (vector<Expr*>::iterator itr = arguments.begin(); itr != arguments.end(); ++itr) {
      delete(*itr);
      *itr = nullptr;
   }

   vector<Expr*> newExprs;
   for (vector<Expr*>::const_iterator itr = other.arguments.begin(); itr != other.arguments.end(); ++itr) {
        newExprs.push_back((*itr)->deepcopy());
   }

   arguments = newExprs;

   return *this;

}

Call::Call (const Call& other) {
   paren = other.paren;
   callee = other.callee;
   arguments = other.arguments;
}

Call* Call::deepcopy () {
   return new Call(*this);
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
