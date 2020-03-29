#include<iostream>
#include<fstream>
#include<iterator>
#include<vector>

using namespace std;

class Lexer {
    vector<Token> tokenArray;
    fstream sourceFile;
    SymTab* symtab;

public:
    Lexer(string sourceFileName,SymTab* st){
        symtab = st;
        sourceFile.open(sourceFileName.c_str());
    }

    void tokenList(){
        char c;
        sourceFile.get(c);
        TokenKind tokenKind;
        
        while(!sourceFile.eof()){
            if(('a'<= c && c <= 'z') || ('A'<=c && c<='Z')){
                string str;

                do {
                    str +=c;
                    sourceFile.get(c);
                } while(('a'<= c && c <= 'z') || ('A'<=c && 'Z'<=c));
                
                if(str == "int"){
                    tokenKind = DATATYPE_INT;
                    Token newToken(tokenKind);
                    this->tokenArray.push_back(newToken);
                } 
                else if(str == "void"){
                    tokenKind = DATATYPE_VOID;
                    Token newToken(tokenKind);
                    this->tokenArray.push_back(newToken);
                }
                else if(str == "return"){
                    tokenKind = RETURN;
                    Token newToken(tokenKind);
                    this->tokenArray.push_back(newToken);
                }
                else {
                    int symtabIndex = (*symtab).push(str);
                    tokenKind = VARIABLE;
                    Token newToken(tokenKind,symtabIndex);
                    this->tokenArray.push_back(newToken);
                }

            }

            else if('0' <= c && c <= '9'){
                int num = c - '0';
                sourceFile.get(c);
                while('0' <= c && c <= '0'){
                    num = num*10 + (int)(c - '0');
                    sourceFile.get(c);
                }
                tokenKind = NUMBER;
                Token newToken(tokenKind,num);
                this->tokenArray.push_back(newToken);
            } 
            
            else {
                switch(c) {
                    case '(' : {
                        tokenKind = BRACKET_SMALL_OPEN;
                        Token newToken(tokenKind);
                        this->tokenArray.push_back(newToken);
                        break;
                    }
                    case ')' : {
                        tokenKind = BRACKET_SMALL_CLOSE;
                        Token newToken(tokenKind);
                        this->tokenArray.push_back(newToken);
                        break;
                    }
                    case '{' : {
                        tokenKind = BRACKET_CURLY_OPEN;
                        Token newToken(tokenKind);
                        this->tokenArray.push_back(newToken);
                        break;
                    }
                    case '}' : {
                        tokenKind = BRACKET_CURLY_CLOSE;
                        Token newToken(tokenKind);
                        this->tokenArray.push_back(newToken);
                        break;
                    }
                    case ';' : {
                        tokenKind = SEMICOLON;
                        Token newToken(tokenKind);
                        this->tokenArray.push_back(newToken);
                        break;
                    }
                    case '=' : {
                        tokenKind = ASSIGNMENT;
                        Token newToken(tokenKind);
                        this->tokenArray.push_back(newToken);
                        break;
                    }
                }
                sourceFile.get(c);
            }

        }
    }

    void print(){
        for(int i= 0;i < this->tokenArray.size();i++){
            cout<<"Type: "<<this->tokenArray[i].kind<<" Value: "<<this->tokenArray[i].value<<endl;
        }
    }

    vector<Token>& giveAccess(){
        return this->tokenArray;
    }
};