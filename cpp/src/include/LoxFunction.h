# ifndef LOX_FUNCTION
# define LOX_FUNCTION

# include "Object.h"
# include "Interpreter.h"
# include <vector>
# include "LoxCallable.h"
# include "Environment.h"
# include "LoxInstance.h"

class LoxFunction: public LoxCallable {
    public:
        LoxFunction(Function *declaration, Environment *environment, bool isInitializer);
        Object* call(Interpreter interpreter, vector<Object*>arguments);
        int arity();
        Function* getdeclaration();
        string toString();
        LoxFunction* bind(LoxInstance *instance);
    private:
        Function *declaration;
        Environment *closure;
        bool isInitializer;
};

# endif