# ifndef LOX_FUNCTION
# define LOX_FUNCTION

# include "Object.h"
# include "Interpreter.h"
# include <vector>
# include "LoxCallable.h"
# include "Environment.h"

class LoxFunction: public LoxCallable {
    public:
        LoxFunction(Function *declaration, Environment *environment);
        Object* call(Interpreter interpreter, vector<Object*>arguments);
        int arity();
        Function* getdeclaration();
        string toString();
    private:
        Function *declaration;
        Environment *closure;
};

# endif