# include "Expr.h"
# include "Stmt.h"
# include "VisitorStmtBase.h"
# include "Var.h"

# include <any>
using namespace std;

Var::Var (Token name, Expr *initializer) {
    this -> initializer =  initializer;
    this -> name = name;
};

Var::~Var () {
    delete initializer;
}

Var& Var::operator= (const Var& other) {
    if (this == &other) {
        return *this;
    }

    name = other.name;
    delete initializer;
    initializer = nullptr;
    initializer = other.initializer->deepcopy();
    return *this;
}

Var::Var (const Var& other) {
    name = other.name;
    initializer = other.initializer;
}

Var* Var::deepcopy () {
    return new Var(*this);
}

Expr* Var::getinitializer() {
   return this -> initializer;
}

Token Var::getToken () {
    return this -> name;
}

any Var::accept (VisitorStmtBase& visitor) {
   return visitor.visitVarStmtBase(*this);
}