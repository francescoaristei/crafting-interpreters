# include "Object.h"
# include "Expr.h"
# include "Literal.h"
# include "VisitorExprBase.h"

# include <any>
using namespace std;


Literal::Literal (Object *value) {
    this ->  value =  value;
};

Literal::~Literal () {
   delete value;
}

Literal& Literal::operator= (const Literal& other) {
   if (this == &other) {
      return *this;
   }

   delete value;
   value = nullptr;
   value = other.value;
   return *this;
}

Literal::Literal (const Literal& other) {
   value = other.value;
}

Literal* Literal::deepcopy () {
   return new Literal(*this);
}

Object* Literal::getvalue() {
   return this -> value;
}

any Literal::accept (VisitorExprBase& visitor) {
   return visitor.visitLiteralExprBase(*this);
}