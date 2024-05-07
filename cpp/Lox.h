# ifndef LOX
# define LOX
# include <list>
# include <fstream>
# include <iostream>
# include <exception>


using namespace std;

class Lox {
    public:
        static bool hadError;
        static void runFile (string path);
        static void runPrompt ();
        static void error (int line, string msg);
        static void report (int line, string where, string msg);
    
    private:
        static void run (string source);
};

# endif


