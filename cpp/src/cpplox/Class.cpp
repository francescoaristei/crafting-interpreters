# include "Expr.h"
# include "Stmt.h"
# include "Class.h"
# include "VisitorStmtBase.h"
# include "Function.h"
# include "Variable.h"
# include <vector>

# include <any>
using namespace std;

Class::Class (Token *name, Variable *superclass, vector<Stmt*> methods) {
    this ->  name = name;
    this -> methods = methods;
    this -> superclass = superclass;
};

/*Class::~Class () {
   delete superclass;
   for (vector<Stmt*>::iterator itr = methods.begin(); itr != methods.end(); ++itr) {
        delete *itr;
    }
}

Class& Class::operator= (const Class& other) {
   if (this == &other) {
      return *this;
   }

   delete superclass;
   superclass = nullptr;
   superclass = other.superclass->deepcopy();

   for (vector<Stmt*>::iterator itr = methods.begin(); itr != methods.end(); ++itr) {
      delete *itr;
      *itr = nullptr;
    }

   vector<Stmt*> newstmts;
   for (vector<Stmt*>::const_iterator itr = other.methods.begin(); itr != other.methods.end(); ++itr) {
      newstmts.push_back((*itr)->deepcopy());
   }
   
   methods = newstmts;

   return *this;

}

Class::Class (const Class& other) {
   name = other.name;
   superclass = other.superclass;
   methods = other.methods;
}

Class* Class::deepcopy () {
   return new Class(*this);

}*/

const vector<Stmt*>& Class::getmethods() const {
   return this -> methods;
}

Token* Class::getname () {
    return this -> name;
}

Variable* Class::getsuperclass () {
   return this -> superclass;
}

any Class::accept (VisitorStmtBase& visitor) {
   return visitor.visitClassStmtBase(*this);
}