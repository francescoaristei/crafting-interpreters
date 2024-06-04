# include "Expr.h"
# include "Stmt.h"
# include "While.h"
# include "VisitorStmtBase.h"

# include <any>
using namespace std;

While::While (Expr *expression, Stmt *stmt) {
    this ->  expression =  expression;
    this -> stmt = stmt;
};

/*While::~While () {
   delete expression;
   delete stmt;
}

While& While::operator= (const While& other) {
   if (this == &other) {
      return *this;
   }

   delete expression;
   delete stmt;
   expression = nullptr;
   stmt = nullptr;
   expression = other.expression->deepcopy();
   stmt = other.stmt->deepcopy();
   return *this;
}

While::While (const While& other) {
   expression = other.expression;
   stmt = other.stmt;
}

While* While::deepcopy () {
   return new While(*this);
}*/


Expr* While::getexpression() {
   return this -> expression;
}

Stmt* While::getstmt () {
    return this -> stmt;
}

any While::accept (VisitorStmtBase& visitor) {
   return visitor.visitWhileStmtBase(*this);
}