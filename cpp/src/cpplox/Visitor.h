# ifndef VISITOR
# define VISITOR
# include "Binary.h"
# include "Grouping.h"
# include "Literal.h"
# include "Unary.h"

template <typename R>
class Visitor {
   public:
       virtual R visitBinaryExpr (Binary<R>& expr) = 0;
       virtual R visitGroupingExpr (Grouping<R>& expr) = 0;
       virtual R visitLiteralExpr (Literal<R>& expr) = 0;
       virtual R visitUnaryExpr (Unary<R>& expr) = 0;
};
# endif
