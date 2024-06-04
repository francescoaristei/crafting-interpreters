# include "Expr.h"
# include "Stmt.h"
# include "Return.h"
# include "Token.h"
# include "VisitorStmtBase.h"

# include <any>
using namespace std;

Return::Return (Token keyword, Expr *value) {
    this ->  value =  value;
    this -> keyword = keyword;
};

Return::~Return () {
   delete value;
}

Return& Return::operator= (const Return& other) {
   if (this == &other) {
      return *this;
   }

   keyword = other.keyword;
   delete value;
   value = nullptr;
   value = other.value->deepcopy();
   return *this;
}

Return::Return (const Return& other) {
   value = other.value;
   keyword = other.keyword;
}

Return* Return::deepcopy () {
   return new Return(*this);
}

Expr* Return::getvalue() {
   return this -> value;
}

Token Return::getkeyword () {
    return this -> keyword;
}

any Return::accept (VisitorStmtBase& visitor) {
   return visitor.visitReturnStmtBase(*this);
}