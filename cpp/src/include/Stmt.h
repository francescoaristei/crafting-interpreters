# ifndef STMT_CLASS
# define STMT_CLASS
class VisitorStmtBase;

# include <any>
using namespace std;

class Stmt {
   public:
       virtual any accept (VisitorStmtBase& visitor) = 0;
       //virtual Stmt* deepcopy (){};
};

# endif
