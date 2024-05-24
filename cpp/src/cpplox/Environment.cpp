# include <map>
# include <string>
# include "Object.h"
# include "Token.h"
# include "Environment.h"
# include "Interpreter.h"


using namespace std;

Environment::Environment () {
    enclosing = NULL;
}

Environment::~Environment () {
    delete this -> enclosing;
}

Environment& Environment::operator= (const Environment& rhs) {
    if (this == &rhs) {
        return *this;
    }

    delete enclosing;
    enclosing = NULL;

    Environment *enclosing = rhs.enclosing;
    return *this;
}

Environment::Environment (const Environment& other) : enclosing(NULL) {
    Environment *enclosing = other.enclosing;
}

Environment::Environment (Environment *enclosing) {
    this -> enclosing = enclosing;
}

void Environment::define (string name, Object *value) {
    values[name] = value;
}

Object* Environment::get (Token name) {
    map<string, Object*>::iterator it = values.find(name.getLexeme());
    if (it != values.end()) {
        return it -> second;
    }

    if (enclosing != NULL) return enclosing -> get(name);

    /* make it runtime error instead of syntax (compile time) error to allow referencing before declaring a variable (as in recursion) */
    throw new Interpreter::RuntimeError (name,
        "Undefined variable '" + name.getLexeme() + "'.");
}

/* assigment needs to be distinguished from the definition (done by define)*/
void Environment::assign (Token name, Object *value) {
    map<string, Object*>::iterator it = values.find(name.getLexeme());
    if (it != values.end()) {
        values[name.getLexeme()] = value;
        return;
    }

    if (enclosing != NULL) {
        enclosing -> assign(name, value);
        return;
    }

    throw new Interpreter::RuntimeError(name,
        "Undefined variable '" + name.getLexeme() + "'.");
}