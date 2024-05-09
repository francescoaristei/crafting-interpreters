# ifndef GROUPING
# define GROUPING
# include "Expr.h"

class Grouping: public Expr {
   public: 
       Grouping (Expr expression);
   private: 
       Expr expression;
};
# endif