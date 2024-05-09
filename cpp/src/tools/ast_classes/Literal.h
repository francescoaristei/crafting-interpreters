# ifndef LITERAL
# define LITERAL
# include "Object.h"
# include "Expr.h"

class Literal: public Expr {
   public: 
       Literal (Object value);
   private: 
       Object value;
};
# endif