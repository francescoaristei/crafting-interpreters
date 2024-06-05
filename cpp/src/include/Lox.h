# ifndef LOX_CLASS
# define LOX_CLASS
# include <list>
# include <fstream>
# include <iostream>
# include <exception>
# include "Token.h"
# include "Interpreter.h"

using namespace std;

class Lox {
    public:
        static bool hadError;
        static bool hadRuntimeError;
        static void runFile (string path);
        static void runPrompt ();
        static void error (int line, string msg);
        static void report (int line, string where, string msg);
        static void error (Token *token, string msg);
        static void runtimeError (Interpreter::RuntimeError error);
    
    private:
        static void run (string source);
};

# endif


