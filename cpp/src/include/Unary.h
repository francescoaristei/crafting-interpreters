# ifndef UNARY
# define UNARY
# include "Token.h"
# include "Expr.h"

class VisitorExprBase;

# include <any>
using namespace std;

class Unary: public Expr {
   public: 
       Unary (Token op, Expr *right);
       any accept (VisitorExprBase& visitor);
       Token  getop();
       Expr* getright();
   private: 
       Token op;
       Expr *right;
};

# endif