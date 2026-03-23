#pragma once

#include "Token.h"
#include <string>

class Expr {
public:
    virtual ~Expr() = default;
};

class Binary : public Expr {
public:
    Expr* left;
    Token op;
    Expr* right;

    Binary(Expr* left, Token op, Expr* right)
        : left(left), op(op), right(right) {}
};

class Grouping : public Expr {
public:
    Expr* expression;

    Grouping(Expr* expression)
        : expression(expression) {}
};

class Literal : public Expr {
public:
    std::string value;

    Literal(std::string value)
        : value(value) {}
};

class Unary : public Expr {
public:
    Token op;
    Expr* right;

    Unary(Token op, Expr* right)
        : op(op), right(right) {}
};

