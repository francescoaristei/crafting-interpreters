# include "Stmt.h"
# include "Block.h"
# include <vector>
# include "VisitorStmtBase.h"
# include <any>
using namespace std;

Block::Block (vector<Stmt*> statements) {
    this -> statements = statements;
}

Block::~Block () {
    for (vector<Stmt*>::iterator itr = statements.begin(); itr != statements.end(); ++itr) {
        delete *itr;
    }
}

Block& Block::operator= (const Block& other) {
    if (this == &other)
        return *this;

    for (vector<Stmt*>::iterator itr = statements.begin(); itr != statements.end(); ++itr) {
        delete *itr;
        *itr = nullptr;
    }

    vector<Stmt*> newstmts;
    for (vector<Stmt*>::const_iterator itr = other.statements.begin(); itr != other.statements.end(); ++itr) {
        newstmts.push_back((*itr)->deepcopy());
    }

    statements = newstmts;

    return *this;

}

Block::Block (const Block& other) {
    statements = other.statements;
}

Block* Block::deepcopy () {
    return new Block(*this);
}

vector<Stmt*> Block::getstatements () {
    return this -> statements;
}

any Block::accept (VisitorStmtBase& visitor) {
   return visitor.visitBlockStmtBase(*this);
}


