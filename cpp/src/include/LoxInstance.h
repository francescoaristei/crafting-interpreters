# ifndef LOXINSTANCE_CLASS
# define LOXINSTANCE_CLASS

# include <string>
# include <map>
# include "Object.h"
# include "LoxClass.h"
# include "Token.h"

using namespace std;


class LoxInstance: public Object {
    public:
        LoxInstance (LoxClass *klass);
        string toString ();
        Object* get (Token name);
        void set (Token name, Object *value);
    private:
        LoxClass *klass;
        map<string, Object*> fields;

};

# endif