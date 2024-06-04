# ifndef GROUPING_EXPR
# define GROUPING_EXPR
# include "Expr.h"

# include <any>
using namespace std;

class VisitorExprBase;

class Grouping: public Expr {
   public: 
       Grouping (Expr *expression);
       ~Grouping ();
       Grouping& operator= (const Grouping& other);
       Grouping (const Grouping& other);
       Grouping* deepcopy ();
       any accept (VisitorExprBase& visitor);
       Expr* getexpression();
   private: 
       Expr *expression;
};

# endif