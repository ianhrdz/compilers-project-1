#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Token.h"
#include "Scanner.h"
using namespace std;

void run(const string& source) {
    Scanner scanner(source);
    vector<Token> tokens= scanner.scanTokens();

    for(const Token& token : tokens){
        cout << token.toString() << endl;
    }
    
}


void runFile(const string& path){
    ifstream file(path);

    stringstream buffer;
    buffer << file.rdbuf();

    string source = buffer.str();

    run(source);
}

bool hadError = false;

void runPrompt(){
    string line;

    while(true){
        cout << ">";
        if(!getline(cin,line)) break;

        run(line);
        hadError = false;
    }
}

void report(int line, const std::string& where, const std::string& message);

void error(int line, const std::string& message){
    report(line, "", message);
}

void report(int line, const string& where, const string& message){
    cerr << "[line" << line << "] Error" << where << ": " << message << endl;
    hadError= true;
}

int main(int argc, char* argv[]){
    if(argc > 2){
        cout << "Usage: jlox [script]";
        return 64;
    } else if(argc == 2){
        runFile(argv[1]);
        if(hadError) return 65;
    } else{
        runPrompt();
    }
    
}