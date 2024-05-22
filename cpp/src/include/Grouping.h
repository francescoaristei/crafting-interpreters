# ifndef GROUPING
# define GROUPING
# include "Expr.h"

# include <any>
using namespace std;

class VisitorExprBase;

class Grouping: public Expr {
   public: 
       Grouping (Expr *expression);
       any accept (VisitorExprBase& visitor);
       Expr* getexpression();
   private: 
       Expr *expression;
};

# endif