# ifndef EXPR
# define EXPR
template <typename R> class Visitor;

# include <iostream>

using namespace std;

/* 
TO-DO: remove class template and implement type erasure to obtain same behavior as having accept as a template virtual function (not allowed) 
type erasure: https://www.artima.com/articles/on-the-tension-between-object-oriented-and-generic-programming-in-c
*/
template <typename R>
class Expr {
   public:
       virtual R accept (Visitor<R>& visitor) = 0;
};

# endif
