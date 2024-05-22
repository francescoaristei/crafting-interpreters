# ifndef STMT
# define STMT
class VisitorStmtBase;

# include <any>
using namespace std;

class Stmt {
   public:
       virtual any accept (VisitorStmtBase& visitor) = 0;
};

# endif
