# ifndef LITERAL
# define LITERAL
# include "Object.h"
# include "Expr.h"
template <typename R> class Visitor;

template <typename R>
class Literal: public Expr<R> {
   public: 
       Literal (Object *value);
       R accept (Visitor<R>& visitor) override;
       Object*  getvalue();
   private: 
       Object *value;
};

template <typename R>
Literal<R>::Literal (Object *value) {
    this ->  value =  value;
};

template <typename R>
Object* Literal<R>::getvalue() {
   return this -> value;
}

template <typename R>
R Literal<R>::accept (Visitor<R>& visitor) {
   return visitor.visitLiteralExpr(*this);
}
# endif