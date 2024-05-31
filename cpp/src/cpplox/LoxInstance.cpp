# include "LoxClass.h"
# include "LoxInstance.h"
# include "Object.h"
# include "Interpreter.h"
# include <string>

using namespace std;


LoxInstance::LoxInstance (LoxClass *klass) {
    this -> klass = klass;
}

string LoxInstance::toString () {
    return klass->getname() + " instance";
}



Object* LoxInstance::get (Token name) {
    if (fields.find(name.getLexeme()) != fields.end()) {
        return fields[name.getLexeme()];
    }

    LoxFunction *method = klass->findMethod(name.getLexeme());
    if (method != NULL) return method->bind(this);

    throw new Interpreter::RuntimeError (name, "Undefined property '" + name.getLexeme() + "'.");
}


void LoxInstance::set (Token name, Object *value) {
    fields[name.getLexeme()] = value;
}


