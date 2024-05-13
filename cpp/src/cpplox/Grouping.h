# ifndef GROUPING
# define GROUPING
# include "Expr.h"
template <typename R> class Visitor;
# include <iostream>

template <typename R>
class Grouping: public Expr<R> {
   public: 
       Grouping (Expr<R> *expression);
       R accept (Visitor<R>& visitor) override;
       Expr<R>* getexpression();
   private: 
       Expr<R> *expression;
};

template <typename R>
Grouping<R>::Grouping (Expr<R> *expression) {
    this ->  expression =  expression;
};

template <typename R>
Expr<R>* Grouping<R>::getexpression() {
   return this -> expression;
}

template <typename R>
R Grouping<R>::accept (Visitor<R>& visitor) {
   return visitor.visitGroupingExpr(*this);
}
# endif