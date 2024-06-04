# ifndef LOXCLASS_CLASS
# define LOXCLASS_CLASS

# include <iostream>
# include <string>
# include <vector>
# include "LoxCallable.h"
# include <map>
# include "Object.h"
# include "Interpreter.h"

/* forward declared to avoid circular dependency */
class LoxFunction;


using namespace std;

class LoxClass: public LoxCallable {
    public:
        LoxClass (string name, LoxClass *superclass, map<string, LoxFunction*> methods);
        /*~LoxClass ();
        LoxClass& operator= (const LoxClass& other);
        LoxClass (const LoxClass& other);
        LoxClass* deepcopy ();*/
        string toString ();
        Object* call (Interpreter interpreter, vector<Object*> arguments);
        int arity ();
        string getname ();
        LoxFunction* findMethod (string name);

    private:
        string name;
        map<string, LoxFunction*> methods;
        LoxClass *superclass;

};

# endif