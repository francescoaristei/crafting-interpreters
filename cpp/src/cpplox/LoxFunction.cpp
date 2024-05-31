# include "Object.h"
# include "Interpreter.h"
# include <vector>
# include "LoxFunction.h"
# include "Environment.h"
# include "LoxInstance.h"

LoxFunction::LoxFunction (Function *declaration, Environment *closure, bool isInitializer) {
    this -> declaration = declaration;
    this -> closure = closure;
    this -> isInitializer = isInitializer;
}

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


string LoxFunction::toString() {
    return "<fn" + getdeclaration()->getname().getLexeme() + ">";
}