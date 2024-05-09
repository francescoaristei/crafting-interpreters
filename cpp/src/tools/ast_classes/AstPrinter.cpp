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
# include "AstPrinter.h"

using namespace std;

template <typename R>
R AstPrinter<R>::print (Expr expr) {
    return expr.accept<R>(this);
}

template <typename R>
string AstPrinter<R>::visitBinaryExpr (Binary expr) {
    vector<Expr> exprs;
    exprs.push_back(expr.getleft());
    exprs.push_back(expr.getright());
    return parenthesize(expr.getop().getLexeme(), exprs);
}

template <typename R>
string AstPrinter<R>::visitGroupingExpr (Grouping expr) {
    vector<Expr> exprs;
    exprs.push_back(expr.getexpression());
    return parenthesize("group", exprs);
}

template <typename R>
string AstPrinter<R>::visitLiteralExpr (Literal expr) {
    if (expr.getvalue() == NULL) return "nil";
    return expr.getvalue().toString();
}

template <typename R>
string AstPrinter<R>::visitUnaryExpr (Unary expr) {
    vector<Expr> exprs;
    exprs.push_back(expr.getright());
    return parenthesize(expr.getop().getLexeme(), exprs);
}

template <typename R>
string AstPrinter<R>::parenthesize (string name, vector<Expr>& exprs) {
    string output = "(" + name;
    for (vector<Expr>::iterator itr = exprs.begin(); itr != exprs.end(); ++itr) {
        output += " ";
        output += itr -> accept(this);
    }
    output += ")";
    return output;
}

int main (int argc, char *argv[]) {
    Token tok1(TokenType::MINUS, "-", NULL, 1);
    Token tok2(TokenType::STAR, "*", NULL, 1);
    Double d1(123);
    Double d2(45.67);
    Literal l1(d1);
    Literal l2(d2);
    Grouping gr(l2);
    Unary un(tok1, l1);
    Binary bin(un, tok2, gr);

    Expr expression = bin;
    AstPrinter<string> ast;
    cout << ast.print(expression);
}