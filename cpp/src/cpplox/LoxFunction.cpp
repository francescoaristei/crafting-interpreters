# include "Object.h"
# include "Interpreter.h"
# include <vector>
# include "LoxFunction.h"
# include "Environment.h"
# include "LoxInstance.h"
# include "Function.h"

LoxFunction::LoxFunction (Function *declaration, Environment *closure, bool isInitializer) {
    this -> declaration = declaration;
    this -> closure = closure;
    this -> isInitializer = isInitializer;
}

/*LoxFunction::~LoxFunction () {
   delete declaration;
   delete closure;
}

LoxFunction& LoxFunction::operator= (const LoxFunction& other) {
    if (this == &other) {
        return *this;
    }
    isInitializer = other.isInitializer;
    delete declaration;
    declaration = nullptr;
    declaration = other.declaration->deepcopy();
    delete closure;
    closure = nullptr;
    closure = other.closure->deepcopy();
    return *this;
}

LoxFunction::LoxFunction (const LoxFunction& other) {
    declaration = other.declaration;
    closure = other.closure;
    isInitializer = other.isInitializer;
}

LoxFunction* LoxFunction::deepcopy () {
    return new LoxFunction(*this);
}*/

Object* LoxFunction::call (Interpreter interpreter, vector<Object*> arguments) {
    Environment *environment = new Environment(closure);
    for (int i = 0; i < getdeclaration() -> getparams().size(); i++) {
        environment->define(getdeclaration()->getparams()[i].getLexeme(), arguments[i]);
    }

    try {
        interpreter.executeBlock(declaration->getbody(), environment);
    } catch (Interpreter::ReturnEx returnValue) {
        if (isInitializer) return closure->getAt(0, "this");
        return returnValue.getvalue();
    }

    if (isInitializer) return closure->getAt(0, "this");

    return NULL;
}

int LoxFunction::arity () {
    return getdeclaration() -> getparams().size();
}

LoxFunction* LoxFunction::bind (LoxInstance *instance) {
    Environment *environment = new Environment(closure);
    environment->define("this", instance);
    return new LoxFunction(declaration, environment, isInitializer);
}

Function* LoxFunction::getdeclaration () {
    return this -> declaration;
}

string LoxFunction::toString() {
    return "<fn" + getdeclaration()->getname().getLexeme() + ">";
}