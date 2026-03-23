#include <iostream>
#include <string>
#include <unordered_map>
#include "Scanner.h"
#include "TokenType.h"
#include "Lox.h"

static std::unordered_map<std::string, TokenType> keywords = {
    {"and", TokenType::AND},
    {"class", TokenType::CLASS},
    {"else", TokenType::ELSE},
    {"false", TokenType::FALSE},
    {"for", TokenType::FOR},
    {"fun", TokenType::FUN},
    {"if", TokenType::IF},
    {"nil", TokenType::NIL},
    {"or", TokenType::OR},
    {"print", TokenType::PRINT},
    {"return", TokenType::RETURN},
    {"super", TokenType::SUPER},
    {"this", TokenType::THIS},
    {"true", TokenType::TRUE},
    {"var", TokenType::VAR},
    {"while", TokenType::WHILE}
};

using std::string;
using std::vector;

Scanner::Scanner(const std::string& source) : source(source) {}

std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }
    // EOF token so parser knows its the end of input
    tokens.push_back(Token(TokenType::EOF_TOKEN, "", std::monostate{}, line));

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
          // allows for comments basically
          while (!isAtEnd() && peek() != '\n') advance();
        } else {
          addToken(TokenType::SLASH);
        }
        break;
//whitespace
        case ' ':
        case '\r':
        case '\t':

            break;

        case '\n':
            line++;
            break;
// strings    
        case '"': string(); break;    
//numbers, keywords, and errors        
        default:
            if(isDigit(c)){
                number();
            } else if (isAlpha(c)) {
                identifier();
            } else{ 
                error(line, "Unexpected character,");
            }
            break;
    }
}

char Scanner::advance(){
    return source[current++];
}

void Scanner::addToken(TokenType type){
    addToken(type, std::monostate{});
}

void Scanner::addToken(TokenType type, const LiteralValue& literal){
    std::string text = source.substr(start, current - start);
    tokens.push_back(Token(type, text, literal, line));
}
//helper to handle two character operators 
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

    advance();

    // returns the actual string minus quotes
    std::string value = source.substr(start + 1, current - start - 2);
    addToken(TokenType::STRING, value);
  }

bool Scanner::isDigit(char c){
    return c>= '0' && c <= '9';
}
void Scanner::number(){
     while (isDigit(peek())) advance();

    if (peek() == '.' && isDigit(peekNext())) {

      advance();

      while (isDigit(peek())) advance();
    }

    std::string text = source.substr(start, current - start);
    double value = std::stod(text);
    addToken(TokenType::NUMBER, value);
}

char Scanner::peekNext() {
    if (current + 1 >= source.length()) return '\0';
    return source[current + 1];
}

bool Scanner::isAlpha(char c){
     return (c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
             c == '_';
}

bool Scanner::isAlphaNumeric(char c) {
    return isAlpha(c) || isDigit(c);
  }

void Scanner::identifier(){
    while(isAlphaNumeric(peek())) advance();

    std::string text = source.substr(start, current - start);
    
    auto it = keywords.find(text);
    if (it != keywords.end()) {
        addToken(it->second);
    } else {
        addToken(TokenType::IDENTIFIER);
    }
}