# include "Lox.h"

using namespace std;

int main (int argc, char *argv[]) {
    if (argc > 1) {
        cout << "Usage: cpplox [script]";
        exit(64);
    }
    else if (argc == 1) {
        Lox::runFile(argv[0]);
    }
    else {
        Lox::runPrompt();
    }
}