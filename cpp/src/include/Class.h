# ifndef CLASS_STMT
# define CLASS_STMT
# include "Expr.h"
# include "Stmt.h"
# include "Function.h"
# include "Variable.h"
# include <vector>
class VisitorStmtBase;

# include <any>
using namespace std;

class Class: public Stmt {
   public: 
       Class (Token name, Variable *superclass, vector<Stmt*> methods);
       //~Print ();
       any accept (VisitorStmtBase& visitor);
       Token getname();
       vector<Stmt*> getmethods();
       Variable* getsuperclass ();
   private: 
       Token name;
       vector<Stmt*> methods;
       Variable *superclass;
};

# endif