# ifndef AST_PRINTER
# define AST_PRINTER
# include <string>
# include <iostream>
# include "VisitorExpr.h"
# include "Expr.h"
# include "Binary.h"
# include "Literal.h"
# include "Unary.h"
# include "Grouping.h"
# include <vector>
# include "TokenType.h"
# include "Double.h"
# include <iostream>

using namespace std;

/* Visitor is a class template, AstPrinter extends the concrete implementation of Visitor with string: Visitor<string> */
class AstPrinter: public VisitorExpr<string> {
    public:
        string print(Expr *expr);
        string visitBinaryExpr (Binary& expr);
        string visitGroupingExpr (Grouping& expr);
        string visitLiteralExpr (Literal& expr);
        string visitUnaryExpr (Unary& expr);
    private:
        /* vector of expr instead of variadic argument, bad? */
        string parenthesize (string name, vector<Expr*>& exprs);
};

# endif