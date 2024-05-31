# ifndef SUPER_EXPR
# define SUPER_EXPR
# include "Expr.h"
# include "Token.h"
# include <any>
using namespace std;

class VisitorExprBase;

class Super: public Expr {
   public: 
       Super (Token keyword, Token method);
       //~Grouping ();
       any accept (VisitorExprBase& visitor);
       Token getkeyword ();
       Token getmethod ();
   private: 
       Token keyword;
       Token method;
};

# endif