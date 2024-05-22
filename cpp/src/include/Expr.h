# ifndef EXPR
# define EXPR
class VisitorExprBase;

# include <any>
using namespace std;


class Expr {
   public:
       virtual any accept (VisitorExprBase& visitor) = 0;
};

# endif
