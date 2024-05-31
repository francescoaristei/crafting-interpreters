# include "Expr.h"
# include "Stmt.h"
# include "Class.h"
# include "VisitorStmtBase.h"
# include "Function.h"
# include "Variable.h"
# include <vector>

# include <any>
using namespace std;

Class::Class (Token name, Variable *superclass, vector<Stmt*> methods) {
    this ->  name = name;
    this -> methods = methods;
    this -> superclass = superclass;
};

/*Print::~Print () {
   delete expression;
}*/

vector<Stmt*> Class::getmethods() {
   return this -> methods;
}

Token Class::getname () {
    return this -> name;
}

Variable* Class::getsuperclass () {
   return this -> superclass;
}

any Class::accept (VisitorStmtBase& visitor) {
   return visitor.visitClassStmtBase(*this);
}