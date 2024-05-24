# ifndef ENVIRONMENT_CLASS
# define ENVIRONMENT_CLASS
# include <map>
# include <string>
# include "Object.h"
# include "Token.h"
using namespace std;

class Environment {
    public:
        Environment ();
        ~Environment();
        Environment (Environment *enclosing);
        Environment& operator= (const Environment& rhs);
        Environment (const Environment& other);
        void define (string name, Object *value);
        void assign (Token name, Object *value);
        Object* get (Token name);
    private:
        map<string, Object*> values;
        Environment *enclosing;
};

# endif