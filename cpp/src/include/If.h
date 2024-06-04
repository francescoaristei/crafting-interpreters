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
       /*~If ();
       If& operator= (const If& other);
       If (const If& other);
       If* deepcopy ();*/
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