# ifndef LOX_FUNCTION
# define LOX_FUNCTION

# include "Object.h"
# include "Interpreter.h"
# include <vector>
# include "LoxCallable.h"
# include "Environment.h"
# include "LoxInstance.h"
# include "Function.h"

class LoxFunction: public LoxCallable {
    public:
        LoxFunction(Function *declaration, Environment *environment, bool isInitializer);
        ~LoxFunction ();
        LoxFunction& operator= (const LoxFunction& other);
        LoxFunction (const LoxFunction& other);
        LoxFunction* deepcopy ();
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