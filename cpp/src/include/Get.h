# ifndef GET_EXPR
# define GET_EXPR
# include "Expr.h"
# include "Token.h"
# include <any>
using namespace std;

class VisitorExprBase;

class Get: public Expr {
   public: 
       Get (Expr *object, Token name);
       //~Grouping ();
       any accept (VisitorExprBase& visitor);
       Expr* getobject();
       Token getname ();
   private: 
       Expr *object;
       Token name;
};

# endif