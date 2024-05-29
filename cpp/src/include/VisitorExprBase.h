# ifndef VISITOR_EXPR_BASE
# define VISITOR_EXPR_BASE
# include "Binary.h"
# include "Grouping.h"
# include "Literal.h"
# include "Unary.h"
# include "Variable.h"
# include "Assign.h"
# include "Logical.h"
# include "Call.h"

# include <any>
using namespace std;

class VisitorExprBase {
   public:
       virtual any visitBinaryExprBase (Binary& expr) = 0;
       virtual any visitGroupingExprBase (Grouping& expr) = 0;
       virtual any visitLiteralExprBase (Literal& expr) = 0;
       virtual any visitUnaryExprBase (Unary& expr) = 0;
       virtual any visitVariableExprBase (Variable& expr) = 0;
       virtual any visitAssignExprBase (Assign& expr) = 0;
       virtual any visitLogicalExprBase (Logical& expr) = 0;
       virtual any visitCallExprBase (Call& expr) = 0;
};
# endif
