# ifndef PRINTSTMT
# define PRINTSTMT
# include "Expr.h"
# include "Stmt.h"
class VisitorStmtBase;

# include <any>
using namespace std;

class Print: public Stmt {
   public: 
       Print (Expr *expression);
       any accept (VisitorStmtBase& visitor);
       Expr* getexpression();
   private: 
       Expr *expression;
};

# endif