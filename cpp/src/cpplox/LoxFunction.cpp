# include "Object.h"
# include "Interpreter.h"
# include <vector>
# include "LoxFunction.h"
# include "Environment.h"

LoxFunction::LoxFunction (Function *declaration, Environment *closure) {
    this -> declaration = declaration;
    this -> closure = closure;
}

Object* LoxFunction::call (Interpreter interpreter, vector<Object*> arguments) {
    Environment *environment = new Environment(closure);
    for (int i = 0; i < getdeclaration() -> getparams().size(); i++) {
        environment->define(getdeclaration()->getparams()[i].getLexeme(), arguments[i]);
    }

    try {
        interpreter.executeBlock(declaration->getbody(), environment);
    } catch (Interpreter::ReturnEx returnValue) {
        return returnValue.getvalue();
    }
    return NULL;
}

int LoxFunction::arity () {
    return getdeclaration() -> getparams().size();
}


string LoxFunction::toString() {
    return "<fn" + getdeclaration()->getname().getLexeme() + ">";
}