# ifndef CLASS_STMT
# define CLASS_STMT
# include "Expr.h"
# include "Stmt.h"
# include "Function.h"
# include <vector>
class VisitorStmtBase;

# include <any>
using namespace std;

class Class: public Stmt {
   public: 
       Class (Token name, vector<Stmt*> methods);
       //~Print ();
       any accept (VisitorStmtBase& visitor);
       Token getname();
       vector<Stmt*> getmethods();
   private: 
       Token name;
       vector<Stmt*> methods;
};

# endif