# ifndef LITERAL
# define LITERAL
# include "Object.h"
# include "Expr.h"
# include "Visitor.h"

class Literal: public Expr {
   public: 
       Literal (Object value);
       template <typename R>
       R accept (Visitor<R>& visitor);
       Object getvalue();
   private: 
       Object value;
};
# endif