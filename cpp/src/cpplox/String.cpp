# include "String.h"

using namespace std;

String::String (string value) {
    this -> value = value;
}

String::String (const String& other) {
    value = other.value;
}

String* String::deepcopy () {
    return new String(*this);
}

string String::getValue () {
    return this -> value;
}


string String::toString () {
    return value;
}