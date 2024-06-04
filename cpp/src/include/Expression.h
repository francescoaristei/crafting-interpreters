# ifndef EXPRESSION_STMT
# define EXPRESSION_STMT
# include "Expr.h"
# include "Stmt.h"

# include <any>
using namespace std;

class VisitorStmtBase;

class Expression: public Stmt {
   public: 
       Expression (Expr *expression);
        /*~Expression ();
        Expression& operator= (const Expression& other);
        Expression (const Expression& other);
        Expression* deepcopy ();*/
       any accept (VisitorStmtBase& visitor);
       Expr* getexpression();
   private: 
       Expr *expression;
};
# endif