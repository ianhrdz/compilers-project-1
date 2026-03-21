#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


void runFile(const string& path){
    ifstream file(path);

    stringstream buffer;
    buffer << file.rdbuf();

    string source = buffer.str();

    run(source);
}

void runPrompt(){
    string line;

    while(true){
        cout << ">";
        if(!getline(cin,line)) break;

        run(line);
    }
}

void run(const string& source) {
    Scanner scanner(source);
    vector<Token> tokens= scanner.scanTokens();

    for(const Token& token : tokens){
        cout << token << endl;
    }
    
}

int main(int argc, char* argv[]){
    if(argc > 2){
        cout << "Usage: jlox [script]";
        return 64;
    } else if(argc == 2){
        runFile(argv[1]);
    } else{
        runPrompt();
    }
    
}