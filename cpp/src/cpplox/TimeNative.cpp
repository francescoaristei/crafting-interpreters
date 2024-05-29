# include <vector>
# include "TimeNative.h"
# include "Object.h"
# include "Interpreter.h"
# include <chrono>

using namespace std::chrono;


int TimeNative::arity () {return 0;};

Object* TimeNative::call (Interpreter Interpreter, vector<Object*> arguments) {
    milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    return new Double(static_cast<double>(ms.count() / 1000.0));
}

string TimeNative::toString () {
    return "<native fn>";
}