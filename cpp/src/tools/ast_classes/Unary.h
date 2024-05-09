# ifndef UNARY
# define UNARY
# include "Token.h"
# include "Expr.h"
# include "Visitor.h"

class Unary: public Expr {
   public: 
       Unary (Token op, Expr right);
       template <typename R>
       R accept (Visitor<R>& visitor);
       Token getop();
       Expr getright();
   private: 
       Token op;
       Expr right;
};
# endif