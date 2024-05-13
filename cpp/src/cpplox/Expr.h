# ifndef EXPR
# define EXPR
template <typename R> class Visitor;

# include <iostream>

using namespace std;

template <typename R>
class Expr {
   public:
       virtual R accept (Visitor<R>& visitor) = 0;
};

/*template <typename R>
R Expr<R>::accept (Visitor<R>& visitor) {
   return R();
};*/

# endif
