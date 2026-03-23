#pragma once

#include <vector>
#include "Token.h"
#include "Expr.h"
#include "TokenType.h"
#include <stdexcept>

class Parser {
public:
    Parser(const std::vector<Token>& tokens);
    Expr* parse();

private:
    std::vector<Token> tokens;
    int current = 0;

    Expr* expression();
    Expr* equality();
    Expr* comparison();
    Expr* term();
    Expr* factor();
    Expr* unary();
    Expr* primary();

    bool match(TokenType type);
    bool check(TokenType type) const;
    Token advance();
    bool isAtEnd() const;
    const Token& peek() const;
    const Token& previous() const;
    const Token& consume(TokenType type, const std::string& message);
};