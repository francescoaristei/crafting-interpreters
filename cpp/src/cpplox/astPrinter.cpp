# include <string>
# include <iostream>
# include "VisitorExpr.h"
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
    Literal l1(&d1);
    Literal l2(&d2);
    Grouping gr(&l2);
    Unary un(tok1, &l1);
    Binary bin(&un, tok2, &gr);
    AstPrinter ast;
    cout << ast.print(&bin);
}