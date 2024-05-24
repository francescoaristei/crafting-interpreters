# ifndef BLOCK_STMT
# define BLOCK_STMT
# include "Stmt.h"
# include <vector>
class VisitorStmtBase;

# include <any>
using namespace std;

class Block: public Stmt {
   public: 
       Block (vector<Stmt*> statements);
       ~Block ();
       any accept (VisitorStmtBase& visitor);
       vector<Stmt*> getstatements();
   private: 
       vector<Stmt*> statements;
};

# endif