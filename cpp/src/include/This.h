# ifndef THIS_EXPR
# define THIS_EXPR
# include "Expr.h"
# include "Token.h"
# include <any>
using namespace std;

class VisitorExprBase;

class This: public Expr {
   public: 
       This (Token name);
       //~Grouping ();
       any accept (VisitorExprBase& visitor);
       Token getname ();
   private: 
       Token name;
};

# endif