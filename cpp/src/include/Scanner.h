
# ifndef SCANNER_CLASS
# define SCANNER_CLASS
# include <vector>
# include <map>
# include <stdio.h>
# include "Token.h"
# include "Object.h"


using namespace std;


class Scanner {
    public:
        Scanner (string source);
        vector<Token*> scanTokens();

    private:
        string source;
        vector<Token*> tokens;
        int start = 0;
        int current = 0;
        int line = 1;
        bool isAtEnd();
        void scanToken();
        char advance();
        void addToken(TokenType type);
        void addToken(TokenType type, Object *literal);
        bool match(char c);
        char peek();
        bool isDigit(char c);
        bool isAlpha(char c);
        bool isAlphanumeric(char c);
        void identifier();
        void number();
        void string_token();
        char nextPeek();
        static map<string, TokenType> keywords;
        static map<string, TokenType> initializeKeywords();
};

# endif