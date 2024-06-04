# include "Expr.h"
# include "Get.h"
# include "Token.h"
# include "VisitorExprBase.h"

# include <any>
using namespace std;

Get::Get (Expr *object, Token name) {
    this ->  object =  object;
    this -> name = name;
};

/*Get::~Get () {
   delete object;
}

Get& Get::operator= (const Get& other) {
   if (this == &other) {
      return *this;
   }

   name = other.name;

   delete object;
   object = nullptr;
   object = other.object->deepcopy();
   return *this;

}

Get::Get (const Get& other) {
   name = other.name;
   object = other.object;
}

Get* Get::deepcopy () {
   return new Get(*this);
}*/

Expr* Get::getobject() {
   return this -> object;
}

Token Get::getname () {
    return this -> name;
}

any Get::accept (VisitorExprBase& visitor) {
   return visitor.visitGetExprBase(*this);
}