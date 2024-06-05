# ifndef SET_EXPR
# define SET_EXPR
# include "Expr.h"
# include "Token.h"
# include <any>
using namespace std;

class VisitorExprBase;

class Set: public Expr {
   public: 
       Set (Expr *object, Token *name, Expr *value);
       /*~Set ();
       Set& operator= (const Set& other);
       Set (const Set& other);
       Set* deepcopy ();*/
       any accept (VisitorExprBase& visitor);
       Expr* getobject();
       Expr* getvalue ();
       Token* getname ();
   private: 
       Expr *object;
       Expr *value;
       Token *name;
};

# endif