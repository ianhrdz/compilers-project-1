#pragma once
#include <string>
#include "TokenType.h"

class Token {
public:
    TokenType type;
    std::string lexeme;
    std::string literal; 
    int line;

    Token(TokenType type, const std::string& lexeme,
          const std::string& literal, int line);

    std::string toString() const;
};