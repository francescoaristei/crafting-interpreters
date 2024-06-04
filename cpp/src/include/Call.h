# ifndef CALL_EXPR
# define CALL_EXPR
# include "Expr.h"
# include "Token.h"
# include "Expr.h"
# include <vector>

# include <any>
using namespace std;

class VisitorExprBase;

class Call: public Expr {
   public: 
       Call (Expr *callee, Token paren, vector<Expr*> arguments);
       /*~Call ();
       Call (const Call& other);
       Call& operator= (const Call& other);
       Call* deepcopy ();*/
       any accept (VisitorExprBase& visitor);
       Expr* getcallee();
       Token  getparen();
       vector<Expr*> getarguments();
   private: 
       Expr *callee;
       Token paren;
       vector<Expr*> arguments;
};

# endif