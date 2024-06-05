# ifndef FUNCTION_STMT
# define FUNCTION_STMT
# include "Expr.h"
# include "Stmt.h"
# include <vector>
# include "Token.h"
class VisitorStmtBase;

# include <any>
using namespace std;

class Function: public Stmt {
   public: 
       Function (Token *name, vector<Token*> params, vector<Stmt*> body);
       /*~Function ();
       Function& operator= (const Function& other);
       Function (const Function& other);
       Function* deepcopy ();*/
       any accept (VisitorStmtBase& visitor);
       Token* getname();
       const vector<Token*>& getparams() const;
       const vector<Stmt*>& getbody() const;
   private: 
       Token *name;
       vector<Token*> params;
       vector<Stmt*> body;
};

# endif