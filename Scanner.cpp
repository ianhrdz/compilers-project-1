#include <iostream>
#include "Scanner.h"
#include "TokenType.h"

using std::string;
using std::vector;

Scanner::Scanner(const std::string& source) : source(source) {}

std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }

    
    return tokens;
}

bool Scanner::isAtEnd() const {
     return current >= source.length();
}

void Scanner::scanToken() {
    char c = advance();
    switch (c){
        case '(': addToken(TokenType::LEFT_PAREN); break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '{': addToken(TokenType::LEFT_BRACE); break;
        case '}': addToken(TokenType::RIGHT_BRACE); break;
        case ',': addToken(TokenType::COMMA); break;
        case '.': addToken(TokenType::DOT); break;
        case '-': addToken(TokenType::MINUS); break;
        case '+': addToken(TokenType::PLUS); break;
        case ';': addToken(TokenType::SEMICOLON); break;
        case '*': addToken(TokenType::STAR); break; 
    }
}

char Scanner::advance(){
    return source[current++];
}

void Scanner::addToken(TokenType type){
    addToken(type, "");
}

void Scanner::addToken(TokenType type, std::string literal){
    std::string text = source.substr(start, current - start);
    tokens.push_back(Token(type, text, literal, line));
}