# ifndef OBJECT
# define OBJECT

# include <string>

using namespace std;

class Object {
    public:
        virtual ~Object() {};
        virtual string toString() = 0;
};

# endif