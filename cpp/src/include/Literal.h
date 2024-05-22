# ifndef LITERAL
# define LITERAL
# include "Object.h"
# include "Expr.h"

class VisitorExprBase;

# include <any>
using namespace std;

class Literal: public Expr {
   public: 
       Literal (Object *value);
       any accept (VisitorExprBase& visitor);
       Object*  getvalue();
   private: 
       Object *value;
};
# endif