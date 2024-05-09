# ifndef GROUPING
# define GROUPING
# include "Expr.h"
# include "Visitor.h"

class Grouping: public Expr {
   public: 
       Grouping (Expr expression);
       template <typename R>
       R accept (Visitor<R>& visitor);
       Expr getexpression();
   private: 
       Expr expression;
};
# endif