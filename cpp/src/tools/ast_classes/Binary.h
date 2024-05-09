# ifndef BINARY
# define BINARY
# include "Expr.h"
# include "Token.h"
# include "Expr.h"

class Binary: public Expr {
   public: 
       Binary (Expr left, Token op, Expr right);
   private: 
       Expr left;
       Token op;
       Expr right;
};
# endif