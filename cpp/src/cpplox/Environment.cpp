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

/*Environment::~Environment () {
    delete this -> enclosing;
}

Environment& Environment::operator= (const Environment& other) {
    if (this == &other) {
        return *this;
    }

    delete enclosing;
    enclosing = nullptr;

    enclosing = other.enclosing->deepcopy();
    return *this;
}

Environment::Environment (const Environment& other) {
    enclosing = other.enclosing;
}

Environment* Environment::deepcopy () {
    return new Environment(*this);
}*/

Environment::Environment (Environment *enclosing) {
    this -> enclosing = enclosing;
}

void Environment::define (string name, Object *value) {
    /*if (String *s1 = dynamic_cast<String*>(value)) {
        cout << s1->getValue() << "\n";
    }*/
    values[name] = value;
    //cout << values.size() << "\n";
}

Object* Environment::get (Token *name) {
    map<string, Object*>::iterator it = values.find(name->getLexeme());
    /*for (map<string, Object*>::iterator itr = values.begin(); itr != values.end(); ++itr) {
        cout << itr->first << "\n";
    }*/
    if (it != values.end()) {
        return it -> second;
    }

    if (enclosing != NULL) return enclosing -> get(name);

    /* make it runtime error instead of syntax (compile time) error to allow referencing before declaring a variable (as in recursion) */
    throw new Interpreter::RuntimeError (name,
        "Undefined variable '" + name->getLexeme() + "'.");
}

void Environment::assignAt (int distance, Token *name, Object *value) {
    ancestor(distance)->getValues()[name->getLexeme()] = value;
}

Environment* Environment::getEnclosing () {
    return this -> enclosing;
}

map<string, Object*> Environment::getValues () {
    return this -> values;
}

Environment* Environment::ancestor (int distance) {
    Environment *environment = this;

    for (int i = 0; i < distance; i++) {
        environment = environment->getEnclosing();
    }

    return environment;
}

Object* Environment::getAt (int distance, string name) {
    /*for (map<string,Object*>::iterator itr = values.begin(); itr != values.end(); ++itr) {
        cout << itr->first << "\n";
        cout << distance << "\n";
    }*/
    /*if (String *s1 = dynamic_cast<String*>(ancestor(distance)->getValues()[name])) {
        cout << s1->getValue() << "\n";
    }*/
    return ancestor(distance)->getValues()[name];
}

/* assigment needs to be distinguished from the definition (done by define)*/
void Environment::assign (Token *name, Object *value) {
    map<string, Object*>::iterator it = values.find(name->getLexeme());
    if (it != values.end()) {
        values[name->getLexeme()] = value;
        return;
    }

    if (enclosing != NULL) {
        enclosing -> assign(name, value);
        return;
    }

    throw new Interpreter::RuntimeError(name,
        "Undefined variable '" + name->getLexeme() + "'.");
}