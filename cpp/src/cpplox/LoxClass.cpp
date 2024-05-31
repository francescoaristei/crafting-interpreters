# include "LoxClass.h"
# include "Interpreter.h"
# include "Object.h"
# include "LoxInstance.h"
# include "LoxFunction.h"
# include <string>
# include <vector>
# include <map>

using namespace std;

LoxClass::LoxClass (string name, map<string, LoxFunction*> methods) {
    this -> name = name;
    this -> methods = methods;
}

string LoxClass::getname () {
    return this -> name;
}

string LoxClass::toString () {
    return this -> name;
}

Object* LoxClass::call (Interpreter interpreter, vector<Object*> arguments) {
    LoxInstance *instance = new LoxInstance(this);

    // constructor
    LoxFunction *initializer = findMethod("init");
    if (initializer != NULL) {
        initializer->bind(instance)->call(interpreter, arguments);
    }
    return instance;
}

LoxFunction* LoxClass::findMethod (string name) {
    if (methods.find(name) != methods.end()) {
        return methods[name];
    }
}

int LoxClass::arity () {
    LoxFunction *initializer = findMethod("init");
    if (initializer == NULL) return 0;
    return initializer->arity();
}