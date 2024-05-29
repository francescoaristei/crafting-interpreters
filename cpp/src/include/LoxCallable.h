# ifndef LOX_CALLABLE
# define LOX_CALLABLE

# include "Object.h"
# include "Interpreter.h"
# include <vector>

class LoxCallable: public Object {
    public:
        virtual Object* call(Interpreter interpreter, vector<Object*>arguments) = 0;
        virtual int arity() = 0;
};

# endif