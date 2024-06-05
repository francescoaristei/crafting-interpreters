# ifndef RETURN_STMT
# define RETURN_STMT
# include "Expr.h"
# include "Stmt.h"
# include "Token.h"
class VisitorStmtBase;

# include <any>
using namespace std;

class Return: public Stmt {
   public: 
       Return (Token *keyword, Expr *value);
       /*~Return ();
       Return& operator= (const Return& other);
       Return (const Return& other);
       Return* deepcopy ();*/
       any accept (VisitorStmtBase& visitor);
       Expr* getvalue();
       Token* getkeyword();
   private: 
       Expr *value;
       Token *keyword;
};

# endif