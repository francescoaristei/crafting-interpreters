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
# include "Get.h"
# include "Set.h"
# include "This.h"
# include "Super.h"
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
       virtual any visitGetExprBase (Get& expr) = 0;
       virtual any visitSetExprBase (Set& expr) = 0;
       virtual any visitThisExprBase (This& expr) = 0;
       virtual any visitSuperExprBase (Super& expr) = 0;
};
# endif
