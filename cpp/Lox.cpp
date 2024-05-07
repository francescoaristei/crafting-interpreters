# include <list>
# include <fstream>
# include <iostream>
# include <vector>
# include "Lox.h"
# include <string>
# include "Token.h"
# include "Scanner.h"

using namespace std;

/* initialize the static member (must do it outside header file) */
bool Lox::hadError = false;

void Lox::runFile (string path) {
    /* Reads the lox command from a file, save them and run. */
    fstream file (path, ios::binary | ios::in | ios::out);
    if (!file.is_open()) {
        cout << "Error opening the file, exiting...";
        exit(64);
    }

    vector<unsigned char> bytes;
    unsigned char byte;

    while (file.read(reinterpret_cast<char*> (&byte), sizeof(byte))) {
        bytes.push_back(byte);
    }

    /* build a string from the vector of bytes */
    string source(bytes.begin(), bytes.end());

    /* close file stream */
    file.close();

    run (source);

    if (hadError) {
        exit(65);
    }
}

void Lox::runPrompt () {
    /* 

        Receive lox commands to execute and executes them on fly.
    
     */
    string line;
    for (;;) {
        cout << "> ";
        getline(cin, line);
        /* if getline fails, cin is false  */
        if (!cin) {
            break;
        }
        run (line);
        hadError = false;
    }
}


void Lox::run (string source) {
    /*  
        Runs the commands.
    */
    Scanner scanner(source);
    vector<Token> tokens = scanner.scanTokens();

    for (int i = 0; i < tokens.size(); i++) {
        //cout << tokens[i] << "\n";
    }
}


/* reports syntax errors detected in the source code of input */
void Lox::error (int line, string msg) {
    report (line, "", msg);
}


void Lox::report (int line, string where, string msg) {
    cerr << "[line " << line << "] Error " << where + ": " << msg << "\n";
    Lox::hadError = true;
}
