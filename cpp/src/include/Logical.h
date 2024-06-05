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
       Logical (Expr *left, Token *op, Expr *right);
       /*~Logical ();
       Logical& operator= (const Logical& other);
       Logical (const Logical& other);
       Logical* deepcopy ();*/
       any accept (VisitorExprBase& visitor);
       Expr* getleft();
       Token*  getop();
       Expr* getright();
   private: 
       Expr *left;
       Token *op;
       Expr *right;
};

# endif