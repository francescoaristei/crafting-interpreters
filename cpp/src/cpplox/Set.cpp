# include "Expr.h"
# include "Set.h"
# include "Token.h"
# include "VisitorExprBase.h"

# include <any>
using namespace std;

Set::Set (Expr *object, Token name, Expr *value) {
    this ->  object =  object;
    this -> value = value;
    this -> name = name;
};

/*Set::~Set () {
   delete object;
   delete value;
}

Set& Set::operator= (const Set& other) {
    if (this == &other) {
        return *this;
    }

    name = other.name;
    delete object;
    object = nullptr;
    object = other.object->deepcopy();
    delete value;
    value = nullptr;
    value = other.value->deepcopy();
    return *this;
}

Set::Set (const Set& other) {
    name = other.name;
    object = other.object;
    value = other.value;
}

Set* Set::deepcopy () {
    return new Set(*this);
}*/

Expr* Set::getobject() {
   return this -> object;
}

Token Set::getname () {
    return this -> name;
}

Expr* Set::getvalue () {
    return this -> value;
}

any Set::accept (VisitorExprBase& visitor) {
   return visitor.visitSetExprBase(*this);
}