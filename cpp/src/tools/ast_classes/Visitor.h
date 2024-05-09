# include "Binary.h"
# include "Grouping.h"
# include "Literal.h"
# include "Unary.h"

template <typename R>
class Visitor {
   public:
       virtual ~Visitor() {};
       virtual R visitBinaryExpr (Binary expr) {};
       virtual R visitGroupingExpr (Grouping expr) {};
       virtual R visitLiteralExpr (Literal expr) {};
       virtual R visitUnaryExpr (Unary expr) {};
       
};