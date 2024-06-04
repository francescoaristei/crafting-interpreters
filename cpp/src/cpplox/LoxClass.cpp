# include "LoxClass.h"
# include "Interpreter.h"
# include "Object.h"
# include "LoxInstance.h"
# include "LoxFunction.h"
# include <string>
# include <vector>
# include <map>

using namespace std;

LoxClass::LoxClass (string name, LoxClass *superclass, map<string, LoxFunction*> methods) {
    this -> name = name;
    this -> methods = methods;
    this -> superclass = superclass;
}

LoxClass::~LoxClass () {
   delete superclass;
   for (map<string, LoxFunction*>::iterator itr = methods.begin(); itr != methods.end(); ++itr) {
        delete itr->second;
    }
}

LoxClass& LoxClass::operator= (const LoxClass& other) {
    if (this == &other) {
        return *this;
    }

    name = other.name;
    delete superclass;
    superclass = nullptr;
    superclass = other.superclass->deepcopy();
    
    for (map<string, LoxFunction*>::iterator itr = methods.begin(); itr != methods.end(); ++itr) {
        delete itr->second;
        itr->second = nullptr;
    }

    map<string, LoxFunction*> newmap;

    for (map<string, LoxFunction*>::const_iterator itr = other.methods.begin(); itr != other.methods.end(); ++itr) {
        newmap[itr->first] = itr->second->deepcopy();
    }
    methods = newmap;
    return *this;
}

LoxClass::LoxClass (const LoxClass& other) {
    name = other.name;
    superclass = other.superclass;
    methods = other.methods;
}

LoxClass* LoxClass::deepcopy () {
    return new LoxClass(*this);
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

    if (superclass != NULL) {
        return superclass->findMethod(name);
    }
}

int LoxClass::arity () {
    LoxFunction *initializer = findMethod("init");
    if (initializer == NULL) return 0;
    return initializer->arity();
}