# ifndef PRINT_STMT
# define PRINT_STMT
# include "Expr.h"
# include "Stmt.h"
class VisitorStmtBase;

# include <any>
using namespace std;

class Print: public Stmt {
   public: 
       Print (Expr *expression);
       ~Print ();
       any accept (VisitorStmtBase& visitor);
       Expr* getexpression();
   private: 
       Expr *expression;
};

# endif