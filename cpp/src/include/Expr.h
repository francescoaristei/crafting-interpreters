# ifndef EXPR_CLASS
# define EXPR_CLASS
class VisitorExprBase;

# include <any>
using namespace std;


class Expr {
   public:
       virtual any accept (VisitorExprBase& visitor) = 0;
       //virtual Expr* deepcopy () {};
};

# endif
