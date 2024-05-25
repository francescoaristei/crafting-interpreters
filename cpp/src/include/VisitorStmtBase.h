# ifndef VISITOR_STMT_BASE
# define VISITOR_STMT_BASE
# include "Expression.h"
# include "Print.h"
# include "Var.h"
# include "Block.h"

# include <any>
using namespace std;

class VisitorStmtBase {
   public:
       virtual any visitExpressionStmtBase (Expression& stmt) = 0;
       virtual any visitPrintStmtBase (Print& stmt) = 0;
       virtual any visitVarStmtBase (Var& stmt) = 0;
       virtual any visitBlockStmtBase (Block& stmt) = 0;
};
# endif