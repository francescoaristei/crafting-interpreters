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
       Block& operator= (const Block& other);
       Block (const Block& other);
       Block* deepcopy ();
       any accept (VisitorStmtBase& visitor);
       vector<Stmt*> getstatements();
   private: 
       vector<Stmt*> statements;
};

# endif