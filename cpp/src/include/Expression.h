# ifndef EXPRESSION
# define EXPRESSION
# include "Expr.h"
# include "Stmt.h"

# include <any>
using namespace std;

class VisitorStmtBase;

class Expression: public Stmt {
   public: 
       Expression (Expr *expression);
       any accept (VisitorStmtBase& visitor);
       Expr* getexpression();
   private: 
       Expr *expression;
};
# endif