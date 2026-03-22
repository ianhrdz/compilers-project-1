#pragma once

#include <string>
#include <vector>
#include "Token.h"

class Scanner{
public:
    Scanner(const std::string& source);
    std::vector<Token> scanTokens();
    
private:    
    std::string source;
    std::vector<Token> tokens;

    int start = 0;
    int current = 0;
    int line = 1;

    bool isAtEnd() const;
    void scanToken();
    char advance();
    void addToken(TokenType type);
    void addToken(TokenType type, std::string literal);
    bool match(char expected);
    char peek();
    void string();
    bool isDigit(char c);
    void number();
    char peekNext();
};