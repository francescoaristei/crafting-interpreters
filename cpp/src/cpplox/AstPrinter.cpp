/*# include <string>
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
# include "AstPrinter.h"

using namespace std;

string AstPrinter::print (Expr *expr) {
    return any_cast<string>(expr -> accept(*this));
}

string AstPrinter::visitBinaryExpr (Binary& expr) {
    vector<Expr*> exprs;
    exprs.push_back(expr.getleft());
    exprs.push_back(expr.getright());
    return parenthesize(expr.getop().getLexeme(), exprs);
}

string AstPrinter::visitGroupingExpr (Grouping& expr) {
    vector<Expr*> exprs;
    exprs.push_back(expr.getexpression());
    return parenthesize("group", exprs);
}

string AstPrinter::visitLiteralExpr (Literal& expr) {
    if (expr.getvalue() == NULL) return "nil";
    return expr.getvalue() -> toString();
}

string AstPrinter::visitUnaryExpr (Unary& expr) {
    vector<Expr*> exprs;
    exprs.push_back(expr.getright());
    return parenthesize(expr.getop().getLexeme(), exprs);
}

string AstPrinter::parenthesize (string name, vector<Expr*>& exprs) {
    string output = "(" + name;
    for (typename vector<Expr*>::iterator itr = exprs.begin(); itr != exprs.end(); ++itr) {
        output += " ";
        output += any_cast<string>((*itr) -> accept(*this));
    }
    output += ")";
    return output;
}*/