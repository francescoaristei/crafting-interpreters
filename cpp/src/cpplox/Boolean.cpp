# include "Boolean.h"
# include <string>

using namespace std;

Boolean::Boolean (bool value) {
    this -> value = value;
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