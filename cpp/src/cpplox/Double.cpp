# include "Double.h"
# include <sstream>
# include <string>

using namespace std;

Double::Double (double value) {
    this -> value = value;
}

string Double::toString () {
    ostringstream strs;
    strs << this -> value;
    return strs.str();
}