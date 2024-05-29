# ifndef CALL_EXPR
# define CALL_EXPR
# include "Expr.h"
# include "Token.h"
# include "Expr.h"
# include <vector>

# include <any>
using namespace std;

class VisitorExprBase;

class Call: public Expr {
   public: 
       Call (Expr *callee, Token paren, vector<Expr*> arguments);
       //~Binary ();
       any accept (VisitorExprBase& visitor);
       Expr* getcallee();
       Token  getparen();
       vector<Expr*> getarguments();
   private: 
       Expr *callee;
       Token paren;
       vector<Expr*> arguments;
};

# endif