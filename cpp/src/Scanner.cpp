# include "Scanner.h"
# include <stdio.h>
# include "Token.h"
# include "TokenType.h"
# include <vector>
# include <map>
# include "Lox.h"
# include <string>
# include "Object.h"
# include "String.h"
# include "Double.h"

using namespace std;

map<string, TokenType> Scanner::initializeKeywords () {
    map<string, TokenType> keywords;
    keywords["and"] = AND;
    keywords["class"] = CLASS;
    keywords["else"] = ELSE;
    keywords["false"] = FALSE;
    keywords["for"] = FOR;
    keywords["fun"] = FUN;
    keywords["if"] = IF;
    keywords["nil"] = NIL;
    keywords["or"] = OR;
    keywords["print"] = PRINT;
    keywords["return"] = RETURN;
    keywords["super"] = SUPER;
    keywords["this"] = THIS;
    keywords["true"] = TRUE;
    keywords["var"] = VAR;
    keywords["while"] = WHILE;
    return keywords;
}

map<string, TokenType> Scanner::keywords = Scanner::initializeKeywords();

Scanner::Scanner (string source) {
    this -> source = source;
}

bool Scanner::isAtEnd () {
    return this -> current >= this -> source.length();
}

char Scanner::advance () {
    this -> current++;
    return this -> source[current - 1];
}


void Scanner::addToken (TokenType type) {
    addToken(type, NULL);
}

bool Scanner::match (char c) {
    if (isAtEnd()) return false;
    if (this -> source[this -> current] != c) return false;

    current++;
    return true;
}

char Scanner::peek () {
    if (isAtEnd()) return '\0';
    return this -> source[current];
}

char Scanner::nextPeek () {
    if (current + 1 >= this -> source.length()) return '\0';
    return this -> source[current + 1];
}

bool Scanner::isDigit (char c) {
    return c >= '0' && c <= '9';
}

bool Scanner::isAlpha (char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Scanner::isAlphanumeric (char c) {
    return isDigit(c) || isAlpha(c);
}

void Scanner::string_token () {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') {
            line++;
        }
        advance();
    }

    if (isAtEnd()) {
        Lox::error(line, "Unterminated string.");
        return;
    }

    advance();

    string value = this -> source.substr(start + 1, current - start - 2);
    String *str = new String(value);
    addToken(STRING, str);
}

void Scanner::number () {
    /* advance current until is a digit */
    while (isDigit(peek())) {
        advance();
    }

    /* avoid consuming the dot and continue advancing */
    if (peek() == '.' && isDigit(nextPeek())) {
        advance();

        while (isDigit(peek())) {
            advance();
        }
    }

    /* + 1 and - 1 are done to avoid the starting " and ending " */
    double value = stod(this -> source.substr(this -> start + 1, this -> current - this -> start - 1));
    Double *d = new Double(value);
    addToken(NUMBER, d);
}

void Scanner::identifier () {
    while (isAlphanumeric(peek())) advance();
    TokenType keyword;
    string id = this -> source.substr(start, current - start);
    if (keywords.find(id) == keywords.end()) {
        keyword = IDENTIFIER;
    }
    else {
        keyword = keywords[id];
    }
    addToken(keyword);
}

void Scanner::addToken (TokenType type, Object *literal) {
    string text = this -> source.substr(this -> start, this -> current - this -> start);
    Token tok(type, text, literal, line);
    this -> tokens.push_back(tok);
}

void Scanner::scanToken () {
    /* advances the current and returns the character at current */
    char c = advance();
    switch (c) {
        case '(': addToken(LEFT_PAREN); break;
        case ')': addToken(RIGHT_PAREN); break;
        case '{': addToken(LEFT_BRACE); break;
        case '}': addToken(RIGHT_BRACE); break;
        case ',': addToken(COMMA); break;
        case '.': addToken(DOT); break;
        case '-': addToken(MINUS); break;
        case '+': addToken(PLUS); break;
        case ';': addToken(SEMICOLON); break;
        case '*': addToken(STAR); break;
        case '!':
            addToken(match('=') ? BANG_EQUAL : BANG);
            break;
        case '=':
            addToken(match('=') ? EQUAL_EQUAL : EQUAL);
            break;
        case '<':
            addToken(match('=') ? LESS_EQUAL : LESS);
            break;
        case '>':
            addToken(match('=') ? GREATER_EQUAL : GREATER);
            break;
        case '/':
            if (match('/')) {
                /* 
                reads (and ignores) until it finds the newline char which is
                then handled at the next iteration by the case '\n', incrementing the line variable
                */
                while (peek() != '\n' && !isAtEnd()) advance();
            }
            else {
                addToken(SLASH);
            }
            break;
        case '"':
            string_token();
            break;
        case ' ':
        case '\t':
        case '\r':
            /* groups all the useless spaces, tabs etc. */
            break;
        case '\n':
            this -> line++;
            break;
        default:
            if (isDigit(c)) {
                number();
            } else if (isAlpha(c)) {
                identifier();
            }
            else {
                Lox::error(this -> line, "Character not recognized! \n");
                break;
            }
    }
}

vector<Token> Scanner::scanTokens () {
    while (!isAtEnd()) {
        /* beginning of the lexeme */
        this -> start = this -> current;
        scanToken();
    }

    Token tok(EOFF, "", NULL, line);
    this -> tokens.push_back(tok);
    return tokens;
}