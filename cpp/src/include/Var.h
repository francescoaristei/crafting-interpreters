# ifndef VAR_STMT
# define VAR_STMT
# include "Expr.h"
# include "Stmt.h"
# include "Token.h"
class VisitorStmtBase;

# include <any>
using namespace std;

class Var: public Stmt {
   public: 
       Var (Token name, Expr *initializer);
       //~Var ();
       any accept (VisitorStmtBase& visitor);
       Expr* getinitializer();
       Token getToken();
   private: 
       Expr *initializer;
       Token name;
};

# endif