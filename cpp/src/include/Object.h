# ifndef OBJECT
# define OBJECT

# include <string>

using namespace std;

class Object {
    public:
        virtual ~Object() {};
        /* overriden by subclasses */
        virtual string toString() {return "object";};
};

# endif