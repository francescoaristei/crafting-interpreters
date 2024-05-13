# ifndef BINARY
# define BINARY
# include "Expr.h"
# include "Token.h"
# include "Expr.h"
template <typename R> class Visitor;

template <typename R>
class Binary: public Expr<R> {
   public: 
       Binary (Expr<R> *left, Token op, Expr<R> *right);
       R accept (Visitor<R>& visitor) override;
       Expr<R>* getleft();
       Token  getop();
       Expr<R>* getright();
   private: 
       Expr<R> *left;
       Token op;
       Expr<R> *right;
};

template <typename R>
Binary<R>::Binary (Expr<R> *left, Token op, Expr<R> *right) {
    this ->  left =  left;
    this ->  op =  op;
    this ->  right =  right;
};

template <typename R>
Expr<R>* Binary<R>::getleft() {
   return this -> left;
}

template <typename R>
Token Binary<R>::getop() {
   return this -> op;
}

template <typename R>
Expr<R>* Binary<R>::getright() {
   return this -> right;
}

template <typename R>
R Binary<R>::accept (Visitor<R>& visitor) {
   return visitor.visitBinaryExpr(*this);
}
# endif