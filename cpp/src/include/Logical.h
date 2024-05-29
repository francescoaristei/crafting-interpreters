# ifndef LOGICAL_EXPR
# define LOGICAL_EXPR
# include "Expr.h"
# include "Token.h"
# include "Expr.h"

# include <any>
using namespace std;

class VisitorExprBase;

class Logical: public Expr {
   public: 
       Logical (Expr *left, Token op, Expr *right);
       //~Binary ();
       any accept (VisitorExprBase& visitor);
       Expr* getleft();
       Token  getop();
       Expr* getright();
   private: 
       Expr *left;
       Token op;
       Expr *right;
};

# endif