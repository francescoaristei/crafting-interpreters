# include "Object.h"
# include "Expr.h"
# include "Literal.h"
# include "VisitorExprBase.h"

# include <any>
using namespace std;


Literal::Literal (Object *value) {
    this ->  value =  value;
};

/*Literal::~Literal () {
   delete value;
}*/

Object* Literal::getvalue() {
   return this -> value;
}

any Literal::accept (VisitorExprBase& visitor) {
   return visitor.visitLiteralExprBase(*this);
}