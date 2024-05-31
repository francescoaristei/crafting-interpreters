# ifndef LOXCLASS_CLASS
# define LOXCLASS_CLASS

# include <iostream>
# include <string>
# include <vector>
# include <map>
# include "LoxCallable.h"
# include "Object.h"
# include "Interpreter.h"
# include "LoxFunction.h"


using namespace std;

class LoxClass: public LoxCallable {
    public:
        LoxClass (string name, map<string, LoxFunction*> methods);
        string toString ();
        Object* call (Interpreter interpreter, vector<Object*> arguments);
        int arity ();
        string getname ();
        LoxFunction* findMethod (string name);

    private:
        string name;
        map<string, LoxFunction*> methods;

};

# endif