# ifndef IF_STMT
# define IF_STMT
# include "Expr.h"
# include "Stmt.h"
class VisitorStmtBase;

# include <any>
using namespace std;

class If: public Stmt {
   public: 
       If (Expr *condition, Stmt *thenBranch, Stmt *elseBranch);
       //~If ();
       any accept (VisitorStmtBase& visitor);
       Expr* getexpression();
       Stmt* getThenBranch();
       Stmt* getElseBranch();
   private: 
       Expr *expression;
       Stmt *thenBranch;
       Stmt *elseBranch;
};

# endif