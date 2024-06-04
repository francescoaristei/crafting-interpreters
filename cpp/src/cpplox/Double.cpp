# include "Double.h"
# include <sstream>
# include <string>

using namespace std;

Double::Double (double value) {
    this -> value = value;
}

Double::Double (const Double& other) {
    value = other.value;
}

Double* Double::deepcopy () {
    return new Double(*this);
}

string Double::toString () {
    ostringstream strs;
    strs << this -> value;
    return strs.str();
}

double Double::getValue () {
    return this -> value;
}