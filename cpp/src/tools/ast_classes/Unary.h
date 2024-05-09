# ifndef UNARY
# define UNARY
# include "Token.h"
# include "Expr.h"

class Unary: public Expr {
   public: 
       Unary (Token op, Expr right);
   private: 
       Token op;
       Expr right;
};
# endif