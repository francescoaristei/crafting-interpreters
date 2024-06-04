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
       ~Get ();
       Get& operator= (const Get& other);
       Get (const Get& other);
       Get* deepcopy ();
       any accept (VisitorExprBase& visitor);
       Expr* getobject();
       Token getname ();
   private: 
       Expr *object;
       Token name;
};

# endif