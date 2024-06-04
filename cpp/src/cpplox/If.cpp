# include "Expr.h"
# include "Stmt.h"
# include "If.h"
# include "VisitorStmtBase.h"

# include <any>
using namespace std;

If::If (Expr *expression, Stmt *thenBranch, Stmt *elseBranch) {
    this ->  expression =  expression;
    this -> thenBranch = thenBranch;
    this -> elseBranch = elseBranch;
};

If::~If () {
   delete expression;
   delete thenBranch;
   delete elseBranch;
}


If& If::operator= (const If& other) {
    if (this == &other) {
        return *this;
    }

    delete expression;
    delete thenBranch;
    delete elseBranch;
    expression = nullptr;
    thenBranch = nullptr;
    elseBranch = nullptr;
    expression = other.expression->deepcopy();
    thenBranch = other.thenBranch->deepcopy();
    elseBranch = other.elseBranch->deepcopy();
    return *this;
}

If::If (const If& other) {
    expression = other.expression;
    thenBranch = other.thenBranch;
    elseBranch = other.elseBranch;
}

If* If::deepcopy () {
    return new If(*this);
}

Expr* If::getexpression() {
   return this -> expression;
}

Stmt* If::getThenBranch () {
    return this -> thenBranch;
}

Stmt* If::getElseBranch () {
    return this -> elseBranch;
}

any If::accept (VisitorStmtBase& visitor) {
   return visitor.visitIfStmtBase(*this);
}