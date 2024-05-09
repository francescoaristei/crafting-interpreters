# include "Lox.h"

using namespace std;

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