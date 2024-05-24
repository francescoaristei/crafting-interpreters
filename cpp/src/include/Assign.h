# ifndef ASSIGN_EXPR
# define ASSIGN_EXPR
# include "Expr.h"
# include "Token.h"

# include <any>
using namespace std;

class VisitorExprBase;

class Assign: public Expr {
   public: 
       Assign (Token name, Expr *value);
       //~Assign ();
       any accept (VisitorExprBase& visitor);
       Token  getname();
       Expr* getvalue();
   private: 
       Token name;
       Expr *value;
};

# endif