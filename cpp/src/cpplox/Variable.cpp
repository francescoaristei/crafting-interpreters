# include "Token.h"
# include "Expr.h"
# include "Variable.h"
# include "VisitorExprBase.h"

# include <any>
using namespace std;


Variable::Variable (Token name) {
    this ->  name =  name;
};

Token Variable::getname() {
   return this -> name;
}

Variable::Variable (const Variable& other) {
   name = other.name;
}

Variable* Variable::deepcopy () {
   return new Variable(*this);
}

any Variable::accept (VisitorExprBase& visitor) {
   return visitor.visitVariableExprBase(*this);
}