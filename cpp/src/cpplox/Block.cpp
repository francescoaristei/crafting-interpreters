# include "Stmt.h"
# include "Block.h"
# include <vector>
# include "VisitorStmtBase.h"
# include <any>
using namespace std;

Block::Block (vector<Stmt*> statements) {
    this -> statements = statements;
}

/*Block::~Block () {
    for (vector<Stmt*>::iterator itr = statements.begin(); itr != statements.end(); ++itr) {
        delete *itr;
    }
}*/

vector<Stmt*> Block::getstatements () {
    return this -> statements;
}

any Block::accept (VisitorStmtBase& visitor) {
   return visitor.visitBlockStmtBase(*this);
}


