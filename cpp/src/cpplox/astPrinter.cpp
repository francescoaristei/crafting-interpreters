# include <string>
# include <iostream>
# include "Visitor.h"
//# include "Expr.h"
# include "Binary.h"
# include "Literal.h"
# include "Unary.h"
# include "Grouping.h"
# include <vector>
# include "TokenType.h"
# include "Double.h"
# include "AstPrinter.h"

using namespace std;

int main (int argc, char *argv[]) {
    Token tok1(TokenType::MINUS, "-", NULL, 1);
    Token tok2(TokenType::STAR, "*", NULL, 1);
    Double d1(123);
    Double d2(45.67);
    Literal<string> l1(d1);
    Literal<string> l2(d2);
    Grouping<string> gr(l2);
    Unary<string> un(tok1, l1);
    Binary<string> bin(un, tok2, gr);
    AstPrinter<string> ast;
    cout << ast.print(bin);
}