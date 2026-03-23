#include "Parser.h"

Parser::Parser(const std::vector<Token>& tokens)
    : tokens(tokens) {}

Expr* Parser::parse() {
    try {
        return expression();
    } catch (const std::runtime_error&) {
        return nullptr;
    }
}

Expr* Parser::expression() {
    return equality();
}

Expr* Parser::equality() {
    Expr* expr = comparison();

    while (match(TokenType::BANG_EQUAL) || match(TokenType::EQUAL_EQUAL)) {
        Token op = previous();
        Expr* right = comparison();
        expr = new Binary(expr, op, right);
    }

    return expr;
}

Expr* Parser::comparison() {
    Expr* expr = term();

    while (match(TokenType::GREATER) ||
           match(TokenType::GREATER_EQUAL) ||
           match(TokenType::LESS) ||
           match(TokenType::LESS_EQUAL)) {
        Token op = previous();
        Expr* right = term();
        expr = new Binary(expr, op, right);
    }

    return expr;
}

Expr* Parser::term() {
    Expr* expr = factor();

    while (match(TokenType::MINUS) || match(TokenType::PLUS)) {
        Token op = previous();
        Expr* right = factor();
        expr = new Binary(expr, op, right);
    }

    return expr;
}

Expr* Parser::factor() {
    Expr* expr = unary();

    while (match(TokenType::SLASH) || match(TokenType::STAR)) {
        Token op = previous();
        Expr* right = unary();
        expr = new Binary(expr, op, right);
    }

    return expr;
}

Expr* Parser::unary() {
    if (match(TokenType::BANG) || match(TokenType::MINUS)) {
        Token op = previous();
        Expr* right = unary();
        return new Unary(op, right);
    }

    return primary();
}

Expr* Parser::primary() {
    if (match(TokenType::FALSE)) return new Literal(false);
    if (match(TokenType::TRUE))  return new Literal(true);
    if (match(TokenType::NIL))   return new Literal(nullptr);

    if (match(TokenType::NUMBER) || match(TokenType::STRING)) {
        return new Literal(previous().literal);
    }

    if (match(TokenType::LEFT_PAREN)) {
        Expr* expr = expression();
        consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
        return new Grouping(expr);
    }

    throw std::runtime_error("Expect expression.");
}

bool Parser::match(TokenType type) {
    if (check(type)) {
        advance();
        return true;
    }
    return false;
}

bool Parser::check(TokenType type) const {
    if (isAtEnd()) return false;
    return peek().type == type;
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return tokens[current - 1];
}

bool Parser::isAtEnd() const {
    return peek().type == TokenType::EOF_TOKEN;
}

const Token& Parser::peek() const {
    return tokens[current];
}

const Token& Parser::previous() const {
    return tokens[current - 1];
}

const Token& Parser::consume(TokenType type, const std::string& message) {
    if (check(type)) return tokens[current++];

    throw std::runtime_error(message);
}