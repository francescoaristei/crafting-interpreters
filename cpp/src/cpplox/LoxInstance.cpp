# include "LoxClass.h"
# include "LoxInstance.h"
# include "Object.h"
# include "Interpreter.h"
# include "LoxFunction.h"
# include <string>


using namespace std;


LoxInstance::LoxInstance (LoxClass *klass) {
    this -> klass = klass;
}

/*LoxInstance::~LoxInstance () {
   delete klass;
}

LoxInstance& LoxInstance::operator= (const LoxInstance& other) {
    if (this == &other) {
        return *this;
    }

    delete klass;
    klass = nullptr;
    klass = other.klass->deepcopy();
    return *this;
}

LoxInstance::LoxInstance (const LoxInstance& other) {
    klass = other.klass;
}

LoxInstance* LoxInstance::deepcopy () {
    return new LoxInstance(*this);
}*/

string LoxInstance::toString () {
    return klass->getname() + " instance";
}

Object* LoxInstance::get (Token *name) {
    if (fields.find(name->getLexeme()) != fields.end()) {
        return fields[name->getLexeme()];
    }

    LoxFunction *method = klass->findMethod(name->getLexeme());
    if (method != NULL) return method->bind(this);

    throw new Interpreter::RuntimeError (name, "Undefined property '" + name->getLexeme() + "'.");
}


void LoxInstance::set (Token *name, Object *value) {
    fields[name->getLexeme()] = value;
}


