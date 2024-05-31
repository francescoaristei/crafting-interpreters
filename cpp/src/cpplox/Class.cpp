# include "Expr.h"
# include "Stmt.h"
# include "Class.h"
# include "VisitorStmtBase.h"
# include "Function.h"
# include <vector>

# include <any>
using namespace std;

Class::Class (Token name, vector<Stmt*> methods) {
    this ->  name = name;
    this -> methods = methods;
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

any Class::accept (VisitorStmtBase& visitor) {
   return visitor.visitClassStmtBase(*this);
}