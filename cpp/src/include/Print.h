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
       /*~Print ();
       Print& operator= (const Print& other);
       Print (const Print& other);
       Print* deepcopy ();*/
       any accept (VisitorStmtBase& visitor);
       Expr* getexpression();
   private: 
       Expr *expression;
};

# endif