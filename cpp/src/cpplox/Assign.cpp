# include "Token.h"
# include "Expr.h"
# include "Assign.h"
# include "VisitorExprBase.h"
# include <any>
using namespace std;

Assign::Assign (Token name, Expr *value) {
    this ->  name =  name;
    this ->  value =  value;
};

Assign::~Assign () {
   delete value;
}

Assign& Assign::operator= (const Assign& other) {
   if (this == &other) {
      return *this;
   }
   name = other.name;
   delete value;
   value = nullptr;
   value = other.value->deepcopy();

   return *this;
   
}

Assign::Assign (const Assign& other) {
   name = other.name;
   value = other.value;
}


Assign* Assign::deepcopy () {
   return new Assign(*this);
}

Token Assign::getname() {
   return this -> name;
}

Expr* Assign::getvalue() {
   return this -> value;
}

any Assign::accept (VisitorExprBase& visitor) {
   return visitor.visitAssignExprBase(*this);
}
