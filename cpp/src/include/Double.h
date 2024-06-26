# ifndef DOUBLE_OBJECT
# define DOUBLE_OBJECT

# include "string"
# include "Object.h"

using namespace std;

class Double: public Object {
    public:
        Double(double value);
        string toString();
        double getValue();
        //Double (const Double& other);
        //Double* deepcopy();

    private:
        double value;
};

# endif