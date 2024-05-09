# ifndef BINARY
# define BINARY
# include "Expr.h"
# include "Token.h"
# include "Expr.h"
# include "Visitor.h"

class Binary: public Expr {
   public: 
       Binary (Expr left, Token op, Expr right);
       template <typename R>
       R accept (Visitor<R>& visitor);
       Expr getleft();
       Token getop();
       Expr getright();
   private: 
       Expr left;
       Token op;
       Expr right;
};
# endif