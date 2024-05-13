# ifndef UNARY
# define UNARY
# include "Token.h"
# include "Expr.h"
template <typename R> class Visitor;

template <typename R>
class Unary: public Expr<R> {
   public: 
       Unary (Token op, Expr<R> *right);
       R accept (Visitor<R>& visitor) override;
       Token  getop();
       Expr<R>* getright();
   private: 
       Token op;
       Expr<R>* right;
};

template <typename R>
Unary<R>::Unary (Token op, Expr<R> *right) {
    this ->  op =  op;
    this ->  right =  right;
};

template <typename R>
Token Unary<R>::getop() {
   return this -> op;
}

template <typename R>
Expr<R>* Unary<R>::getright() {
   return this -> right;
}

template <typename R>
R Unary<R>::accept (Visitor<R>& visitor) {
   return visitor.visitUnaryExpr(*this);
}
# endif