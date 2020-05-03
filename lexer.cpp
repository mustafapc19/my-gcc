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
            if(('a'<= c && c <= 'z') || ('A'<=c && c<='Z') || c == (char)34 || c == (char)39 || c == '%' || c == '\\'){
                string str;
                if(c == (char)34){
                    do {
                        str +=c;
                        sourceFile.get(c);
                    }while(c!= (char)34);
                    str += (char)34;
                    // cout<<"STR "<<str<<endl;
                } else {
                    do {
                        str +=c;
                        sourceFile.get(c);
                    } while(('a'<= c && c <= 'z') || ('A'<=c && 'Z'<=c));
                    // cout<<"ELSE STR "<<str<<endl;
                }
                
                
                if(str == "int"){
                    tokenKind = IDENTIFIER_INT;
                    Token newToken(tokenKind);
                    this->tokenArray.push_back(newToken);
                } 
                else if(str == "void"){
                    tokenKind = IDENTIFIER_VOID;
                    Token newToken(tokenKind);
                    this->tokenArray.push_back(newToken);
                }
                else if(str == "char"){
                    tokenKind = IDENTIFIER_CHAR;
                    Token newToken(tokenKind);
                    this->tokenArray.push_back(newToken);
                }
                else if(str == "string"){
                    tokenKind = IDENTIFIER_STRING;
                    Token newToken(tokenKind);
                    this->tokenArray.push_back(newToken);
                }
                else if(str == "return"){
                    tokenKind = RETURN;
                    Token newToken(tokenKind);
                    this->tokenArray.push_back(newToken);
                }
                else if(str == "if"){
                    tokenKind = IF;
                    this->tokenArray.push_back(Token(tokenKind));
                }
                else if(str == "while"){
                    tokenKind = WHILE;
                    this->tokenArray.push_back(Token(tokenKind));
                }
                else if(str == "printf"){
                    tokenKind = PRINTF;
                    this->tokenArray.push_back(Token(tokenKind)); 
                }
                else if(str == "scanf"){
                    tokenKind = SCANF;
                    this->tokenArray.push_back(Token(tokenKind));
                }
                else if(str[0] == (char)39 && str[2] == (char)39){
                    tokenKind = VARIABLE_TYPE_CHAR;
                    this->tokenArray.push_back(Token(tokenKind,(int)str[1]));
                }
                else if(str[0] == (char)34){
                    if(str[str.length()-1] == (char)34){
                        // cerr<<"LEXER::tokenlist All good "<<str<< endl;
                    } else {
                        cerr<<"LEXER::tokenlist All Not good"<<str<< endl;
                    }
                    sourceFile.get(c);
                    tokenKind = LITERAL_STRING;
                    int symtabIndex = symtab->push(str,tokenKind);
                    symtab->setRvalueFlag(symtabIndex);
                    // symtab->setTokenKind(tokenKind);
                    Token newToken(tokenKind,symtabIndex);
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
                        tokenKind = EQUAL;
                        Token newToken(tokenKind);
                        this->tokenArray.push_back(newToken);
                        break;
                    }
                    case '+': {
                        tokenKind = PLUS;
                        Token newToken(tokenKind);
                        this->tokenArray.push_back(newToken);
                        break;
                    }
                    case '-': {
                        tokenKind = MINUS;
                        Token newToken(tokenKind);
                        this->tokenArray.push_back(newToken);
                        break;
                    }
                    case ',': {
                        tokenKind = COMMA;
                        this->tokenArray.push_back(Token(tokenKind));
                        break;
                    }
                    case '&': {
                        tokenKind = AMPERSAND;
                        this->tokenArray.push_back(Token(tokenKind));
                        break;
                    }
                    case '!': {
                        tokenKind = EXCLAIMATION;
                        this->tokenArray.push_back(Token(tokenKind));
                        break;
                    }
                    default: {
                        // cerr<<"LEXER::tokenList unexpected charecter-"<<c<<endl;
                    }
                }
                sourceFile.get(c);
            }

        }
    }

    void print(){
        cout<<endl<<"Lexer::print "<<endl;
        for(int i= 0;i < this->tokenArray.size();i++){
            // cout<<"Type: ";
            // TokenKind tokenKind = (TokenKind)this->tokenArray[i].kind;
            this->tokenArray[i].print();
            cout<<endl;
            // cout<<" Value: "<<this->tokenArray[i].value<<endl;
        }
        cout<<endl<<endl;
    }

    vector<Token>& giveAccess(){
        return this->tokenArray;
    }
};