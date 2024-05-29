# ifndef WHILE_STMT
# define WHILE_STMT
# include "Expr.h"
# include "Stmt.h"
class VisitorStmtBase;

# include <any>
using namespace std;

class While: public Stmt {
   public: 
       While (Expr *expression, Stmt *stmt);
       //~While ();
       any accept (VisitorStmtBase& visitor);
       Expr* getexpression();
       Stmt* getstmt();
   private: 
       Expr *expression;
       Stmt *stmt;
};

# endif