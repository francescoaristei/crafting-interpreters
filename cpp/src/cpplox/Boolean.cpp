# include "Boolean.h"
# include <string>

using namespace std;

Boolean::Boolean (bool value) {
    this -> value = value;
}

Boolean::Boolean (const Boolean& other) {
    value = other.value;
}

Boolean* Boolean::deepcopy () {
    return new Boolean(*this);
}

bool Boolean::getValue () {
    return this -> value;
}

string Boolean::toString () {
    if (this -> value == false) {
        return "false";
    }
    else {
        return "true";
    }
}