#pragma once

#include "Expr.h"
#include "LiteralValue.h"

class Interpreter {
public:
    LiteralValue evaluate(Expr* expr);

private:
    LiteralValue evaluateExpr(Expr* expr);

    bool isTruthy(const LiteralValue& value);
    bool isEqual(const LiteralValue& a, const LiteralValue& b);
};