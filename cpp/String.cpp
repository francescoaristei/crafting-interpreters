# include "String.h"

using namespace std;

String::String (string value) {
    this -> value = value;
}

string String::toString () {
    return value;
}