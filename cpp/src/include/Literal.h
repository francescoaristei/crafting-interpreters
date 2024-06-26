# ifndef LITERAL_EXPR
# define LITERAL_EXPR
# include "Object.h"
# include "Expr.h"

class VisitorExprBase;

# include <any>
using namespace std;

class Literal: public Expr {
   public: 
       Literal (Object *value);
       /*~Literal();
       Literal& operator= (const Literal& other);
       Literal (const Literal& other);
       Literal* deepcopy ();*/
       any accept (VisitorExprBase& visitor);
       Object*  getvalue();
   private: 
       Object *value;
};
# endif