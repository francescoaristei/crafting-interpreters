# ifndef TIME_NATIVE
# define TIME_NATIVE

# include <vector>
# include "LoxCallable.h"
# include "Object.h"
# include "Interpreter.h"


class TimeNative: public LoxCallable {
    public:
        int arity();
        Object* call(Interpreter Interpreter, vector<Object*> arguments);
        string toString();
};

# endif