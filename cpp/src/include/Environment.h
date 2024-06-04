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
        //~Environment();
        Environment (Environment *enclosing);
        /*Environment& operator= (const Environment& other);
        Environment* deepcopy ();
        Environment (const Environment& other);*/
        void define (string name, Object *value);
        void assign (Token name, Object *value);
        Object* get (Token name);
        Object* getAt (int distance, string name);
        map<string, Object*> getValues();
        Environment* ancestor (int distance);
        Environment* getEnclosing ();
        void assignAt (int distance, Token name, Object *value);
    private:
        map<string, Object*> values;
        Environment *enclosing;
};

# endif