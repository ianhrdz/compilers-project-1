#include <iostream>
#include "Scanner.h"
#include "TokenType.h"
#include "Lox.h"

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
        case '!': 
            addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG); break;
        case '=': 
            addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL); break;
        case '<': 
            addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS); break;
        case '>': 
            addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER); break; 
        case '/':
        if (match('/')) {
          // A comment goes until the end of the line.
          while (!isAtEnd() && peek() != '\n') advance();
        } else {
          addToken(TokenType::SLASH);
        }
        break;
        case ' ':
        case '\r':
        case '\t':
        // Ignore whitespace
            break;

        case '\n':
            line++;
            break;
        case '"': string(); break;    

        default: 
            error(line, "Unexpected character,");
            break;
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

bool Scanner::match(char expected){
    if (isAtEnd()) return false;
    if (source[current]!= expected) return false;

    current++;
    return true;
}

char Scanner::peek(){
    if (isAtEnd()) return '\0';
    return source[current];
}

void Scanner::string() {
    while (peek() != '"' && !isAtEnd()) {
      if (peek() == '\n') line++;
      advance();
    }

    if (isAtEnd()) {
      error(line, "Unterminated string.");
      return;
    }

    // The closing ".
    advance();

    // Trim the surrounding quotes.
    std::string value = source.substr(start + 1, current - start - 2);
    addToken(TokenType::STRING, value);
  }