# include "Lox.h"

using namespace std;

/* 
TO-DO: remove class template and implement type erasure to obtain same behavior as having accept as a template virtual function (not allowed) 
type erasure: https://www.artima.com/articles/on-the-tension-between-object-oriented-and-generic-programming-in-c
*/

int main (int argc, char *argv[]) {
    if (argc > 2) {
        cout << "Usage: cpplox [script]";
        exit(64);
    }
    /* the first argument is the name of the file */
    else if (argc == 2) {
        Lox::runFile(argv[1]);
    }
    else {
        Lox::runPrompt();
    }
}