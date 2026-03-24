#include "Interpreter.h"
#include <stdexcept>
#include <iostream>

LiteralValue Interpreter::evaluate(Expr* expr) {
    return evaluateExpr(expr);
}

LiteralValue Interpreter::evaluateExpr(Expr* expr) {

    // Literal
    if (auto literal = dynamic_cast<Literal*>(expr)) {
        return literal->value;
    }

    // Grouping
    if (auto group = dynamic_cast<Grouping*>(expr)) {
        return evaluateExpr(group->expression);
    }

    // Unary
    if (auto unary = dynamic_cast<Unary*>(expr)) {
        LiteralValue right = evaluateExpr(unary->right);

        switch (unary->op.type) {
            case TokenType::MINUS:
                if (!std::holds_alternative<double>(right)) {
                    throw std::runtime_error("Operand must be a number.");
                }
                return -std::get<double>(right);

            case TokenType::BANG:
                return !isTruthy(right);

            default:
                break;
        }
    }

    // Binary
    if (auto binary = dynamic_cast<Binary*>(expr)) {
        LiteralValue left = evaluateExpr(binary->left);
        LiteralValue right = evaluateExpr(binary->right);

        switch (binary->op.type) {

            case TokenType::PLUS:
                if (std::holds_alternative<double>(left) &&
                    std::holds_alternative<double>(right)) {
                    return std::get<double>(left) + std::get<double>(right);
                }

                if (std::holds_alternative<std::string>(left) &&
                    std::holds_alternative<std::string>(right)) {
                    return std::get<std::string>(left) + std::get<std::string>(right);
                }

                throw std::runtime_error("Operands must be two numbers or two strings.");

            case TokenType::MINUS:
                return std::get<double>(left) - std::get<double>(right);

            case TokenType::STAR:
                return std::get<double>(left) * std::get<double>(right);

            case TokenType::SLASH:
                return std::get<double>(left) / std::get<double>(right);

            case TokenType::GREATER:
                return std::get<double>(left) > std::get<double>(right);

            case TokenType::GREATER_EQUAL:
                return std::get<double>(left) >= std::get<double>(right);

            case TokenType::LESS:
                return std::get<double>(left) < std::get<double>(right);

            case TokenType::LESS_EQUAL:
                return std::get<double>(left) <= std::get<double>(right);

            case TokenType::EQUAL_EQUAL:
                return isEqual(left, right);

            case TokenType::BANG_EQUAL:
                return !isEqual(left, right);

            default:
                break;
        }
    }

    throw std::runtime_error("Unknown expression.");
}

bool Interpreter::isTruthy(const LiteralValue& value) {
    if (std::holds_alternative<std::nullptr_t>(value)) return false;
    if (std::holds_alternative<bool>(value)) return std::get<bool>(value);
    return true;
}

bool Interpreter::isEqual(const LiteralValue& a, const LiteralValue& b) {
    return a == b;
}