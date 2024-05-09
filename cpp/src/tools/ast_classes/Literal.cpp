# include "Literal.h"
# include "Object.h"
# include "Visitor.h"

Literal::Literal (Object value) {
    this ->  value =  value;

};
Object Literal::getvalue() {
   return this -> value;
}

template <typename R>
R Literal::accept (Visitor<R>& visitor) {
   return visitor.visitLiteralExpr(this);
}
