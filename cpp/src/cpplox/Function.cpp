# include "Expr.h"
# include "Stmt.h"
# include "Function.h"
# include <vector>
# include "Token.h"
# include "VisitorStmtBase.h"

# include <any>
using namespace std;

Function::Function (Token *name, vector<Token*> params, vector<Stmt*> body) {
    this ->  name =  name;
    this -> params = params;
    this -> body = body;
};

/*Function::~Function () {
   for (vector<Stmt*>::iterator itr = body.begin(); itr != body.end(); ++itr) {
        delete *itr;
    }
}

Function& Function::operator= (const Function& other) {
    if (this == &other) {
        return *this;
    }

    name = other.name;
    params = other.params;

    for (vector<Stmt*>::iterator itr = body.begin(); itr != body.end(); ++itr) {
        delete *itr;
        *itr = nullptr;
    }

    vector<Stmt*> newStmts;

    for (vector<Stmt*>::const_iterator itr = other.body.begin(); itr != other.body.end(); ++itr) {
        newStmts.push_back((*itr)->deepcopy());
    }

    body = newStmts;

    return *this;
}


Function::Function (const Function& other) {
    name = other.name;
    params = other.params;
    body = other.body;
}

Function* Function::deepcopy () {
    return new Function(*this);
}*/

Token* Function::getname() {
   return this -> name;
}

const vector<Token*>& Function::getparams () const {
    return this -> params;
}

const vector<Stmt*>& Function::getbody () const {
    return this -> body;
}

any Function::accept (VisitorStmtBase& visitor) {
   return visitor.visitFunctionStmtBase(*this);
}