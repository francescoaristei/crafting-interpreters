# include "Visitor.h"
class Expr {
   template <typename R>
   R accept (Visitor<R>& visitor) {};
};