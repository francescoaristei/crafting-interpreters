# ifndef AST_PRINTER
# define AST_PRINTER
# include <string>
# include <iostream>
# include "Visitor.h"
# include "Expr.h"
# include "Binary.h"
# include "Literal.h"
# include "Unary.h"
# include "Grouping.h"
# include <vector>
# include "TokenType.h"
# include "Double.h"

using namespace std;

/* Visitor is a class template, AstPrinter extends the concrete implementation of Visitor with string: Visitor<string> */
template <typename R>
class AstPrinter: public Visitor<R> {
    public:
        R print(Expr expr);
        virtual string visitBinaryExpr (Binary expr);
        virtual string visitGroupingExpr (Grouping expr);
        virtual string visitLiteralExpr (Literal expr);
        virtual string visitUnaryExpr (Unary expr);
    private:
        /* vector of expr instead of variadic argument, bad? */
        string parenthesize (string name, vector<Expr>& exprs);
};
# endif