# ifndef UNARY_EXPR
# define UNARY_EXPR
# include "Token.h"
# include "Expr.h"

class VisitorExprBase;

# include <any>
using namespace std;

class Unary: public Expr {
   public: 
       Unary (Token op, Expr *right);
       //~Unary ();
       any accept (VisitorExprBase& visitor);
       Token  getop();
       Expr* getright();
   private: 
       Token op;
       Expr *right;
};

# endif