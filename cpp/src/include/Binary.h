# ifndef BINARY
# define BINARY
# include "Expr.h"
# include "Token.h"
# include "Expr.h"

# include <any>
using namespace std;

class VisitorExprBase;

class Binary: public Expr {
   public: 
       Binary (Expr *left, Token op, Expr *right);
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