# ifndef VARIABLE_EXPR
# define VARIABLE_EXPR
# include "Token.h"
# include "Expr.h"

class VisitorExprBase;

# include <any>
using namespace std;

class Variable: public Expr {
   public: 
       Variable (Token *name);
       any accept (VisitorExprBase& visitor);
       Token* getname();
       //Variable (const Variable& other);
       //Variable* deepcopy();
   private: 
       Token *name;
};

# endif