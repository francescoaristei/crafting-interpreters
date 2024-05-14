# ifndef BOOLEAN_OBJECT
# define BOOLEAN_OBJECT

# include "string"
# include "Object.h"

using namespace std;

class Boolean: public Object {
    public:
        Boolean(bool value);
        string toString();
        bool getValue();

    private:
        bool value;
};

# endif