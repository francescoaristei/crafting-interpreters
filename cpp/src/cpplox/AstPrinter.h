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
# include <iostream>

using namespace std;

/* Visitor is a class template, AstPrinter extends the concrete implementation of Visitor with string: Visitor<string> */
template <typename R>
class AstPrinter: public Visitor<string> {
    public:
        string print(Expr<R> *expr);
        string visitBinaryExpr (Binary<R>& expr);
        string visitGroupingExpr (Grouping<R>& expr);
        string visitLiteralExpr (Literal<R>& expr);
        string visitUnaryExpr (Unary<R>& expr);
    private:
        /* vector of expr instead of variadic argument, bad? */
        string parenthesize (string name, vector<Expr<R>*>& exprs);
};

template <typename R>
string AstPrinter<R>::print (Expr<R> *expr) {
    return expr -> accept(*this);
}

template <typename R>
string AstPrinter<R>::visitBinaryExpr (Binary<R>& expr) {
    vector<Expr<R>*> exprs;
    exprs.push_back(expr.getleft());
    exprs.push_back(expr.getright());
    return parenthesize(expr.getop().getLexeme(), exprs);
}

template <typename R>
string AstPrinter<R>::visitGroupingExpr (Grouping<R>& expr) {
    vector<Expr<R>*> exprs;
    exprs.push_back(expr.getexpression());
    return parenthesize("group", exprs);
}

template <typename R>
string AstPrinter<R>::visitLiteralExpr (Literal<R>& expr) {
    if (expr.getvalue() == NULL) return "nil";
    return expr.getvalue() -> toString();
}

template <typename R>
string AstPrinter<R>::visitUnaryExpr (Unary<R>& expr) {
    vector<Expr<R>*> exprs;
    exprs.push_back(expr.getright());
    return parenthesize(expr.getop().getLexeme(), exprs);
}

template <typename R>
string AstPrinter<R>::parenthesize (string name, vector<Expr<R>*>& exprs) {
    string output = "(" + name;
    for (typename vector<Expr<R>*>::iterator itr = exprs.begin(); itr != exprs.end(); ++itr) {
        output += " ";
        output += (*itr) -> accept(*this);
    }
    output += ")";
    return output;
}
# endif