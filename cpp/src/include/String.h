# ifndef STRING_OBJECT
# define STRING_OBJECT

# include "string"
# include "Object.h"

using namespace std;

class String: public Object {
    public:
        String (string value);
        string toString();
        string getValue();
        String (const String& other);
        String* deepcopy();
    private:
        string value;
};

# endif