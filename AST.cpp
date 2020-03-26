#include<iostream>
#include<vector>
#include<iterator>

using namespace std;



class AST{
    vector<Token> tokenArray;
    vector<Token>::iterator iterator;
    int flag;
    SymTab* symtab;
    
public: 
    AST(vector<Token> ta,SymTab* st){
        symtab = st;
        flag = 1;
        for(vector<Token>::iterator it = ta.begin();it < ta.end();it++){
            this->tokenArray.push_back(*it);
        }
        iterator = tokenArray.begin();
        this->init();
        if(this->flag){
            cout<<"ALL SET"<<endl;
        }

    }
    

    void init(){
        TokenKind tokenKind = (TokenKind)((*iterator).kind);
        Token currToken;
        Token nextToken;

        while(tokenKind != BRACKET_CURLY_OPEN && this->flag){
            tokenKind = (TokenKind)((*iterator).kind);
            currToken = (*iterator);
            iterator++;
            nextToken = (*iterator);
            string nextTokenValue;
            string tokenValue;

            switch(tokenKind){
                case DATATYPE_INT :
                case DATATYPE_VOID:
                    nextTokenValue = (*symtab).indexToString((nextToken).value);
                    if( (TokenKind)(nextToken.kind) != VARIABLE || nextTokenValue != "main"){
                        cerr<<"ERROR : At WordIndex "<<iterator-tokenArray.begin()+1;
                        this->flag = 0;
                    }
                    break;
                case VARIABLE :
                    tokenValue = (*symtab).indexToString((currToken).value);
                    if((TokenKind)(nextToken.kind) != BRACKET_SMALL_OPEN || tokenValue != "main"){
                        cerr<<"ERROR : At WordIndex "<<iterator-tokenArray.begin()+1;
                        this->flag = 0;
                    }
                    break;
                case BRACKET_SMALL_OPEN:
                    if((TokenKind)(nextToken.kind) != BRACKET_SMALL_CLOSE){
                        cerr<<"ERROR : At WordIndex "<<iterator-tokenArray.begin()+1;
                        this->flag = 0;
                    }
                    break;
                case BRACKET_SMALL_CLOSE:
                    if((TokenKind)(nextToken.kind) != BRACKET_CURLY_OPEN){
                        cerr<<"ERROR : At WordIndex "<<iterator-tokenArray.begin()+1;
                        this->flag = 0;
                    }
                    break;
                default: 
                    cout<<"Test";
                    break;
            }
        }
    }


/*

    void init(){
        while((*iterator).kind != "BRACKET/CURLY/OPEN" && this->flag){
            iterator++;
            TokenKind tokenKind = (TokenKind)((*iterator).kind)
            switch(tokenKind){
                case "VARIABLE void":
                case "VARIABLE int":
                    if((*iterator).kind != "VARIABLE main"){
                        this->flag = 0;
                    }
                    break;
                case "VARIABLE main":
                    if((*iterator).kind != "BRACKET/SMALL/OPEN"){
                        this->flag = 0;
                    }
                    break;
                case "BRACKET/SMALL/OPEN":
                    if((*iterator).kind != "BRACKET/SMALL/CLOSE"){
                        this->flag = 0;
                    }
                    break;
                case "BRACKET/SMALL/CLOSE":
                    if((*iterator).kind != "BRACKET/CURLY/OPEN"){
                        this->flag = 0;
                    }
                    break;
            }
        }
    }
*/

    void print(){
        for(int i= 0;i < this->tokenArray.size();i++){
            cout<<"AST:Type: "<<this->tokenArray[i].kind<<" Value: "<<this->tokenArray[i].value<<endl;
        }
    }
};