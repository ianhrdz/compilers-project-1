// AST expression node structure based on "Crafting Interpreters" by Robert Nystrom but I used chatgpt sort of to explain and translate concepts and syntax
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
    LiteralValue value;

    Literal(const LiteralValue& value)
        : value(value) {}
};

class Unary : public Expr {
public:
    Token op;
    Expr* right;

    Unary(Token op, Expr* right)
        : op(op), right(right) {}
};

