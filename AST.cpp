#include<iostream>
#include<vector>
#include<iterator>
#include <cstdlib>
#include<queue>

using namespace std;



class AST{
    vector<Token> tokenArray;
    vector<Token>::iterator iterator;
    int flag;
    SymTab* symtab;
    Node* root;
    Node* currNodePtr;
    TokenKind currTokenKind;
    Token currToken;

public: 
    AST(vector<Token> ta,SymTab* st){
        symtab = st;
        flag = 1;
        for(vector<Token>::iterator it = ta.begin();it < ta.end();it++){
            this->tokenArray.push_back(*it);
        }
        iterator = tokenArray.begin();
        this->init();
        if(!this->flag){
            exit(EXIT_FAILURE);
        }
        root = new Node();
        root->changeToken(Token(MAIN,0));
        currTokenKind = (TokenKind)((*iterator).kind);
        switch(currTokenKind){
            case RETURN :
                this->returnDFA();
                break;
            default:
                cerr<<"Expected return keyword : "<<currTokenKind<<endl;
        }

    }
    



    void returnDFA(){
        root->children.push_back(new Node(Token(RETURN),root));
        currNodePtr = (this->root->findChildByType(RETURN) != nullptr) ?
                         (this->root->findChildByType(RETURN)) : new Node();

        exprDFA();
        return;
    }

    void exprDFA(){
        if(*currNodePtr == Node()){
            cerr<< "exprDFA() :: currNode is nullptr";
            return;
        }

        iterator++;
        currTokenKind = (TokenKind)((*iterator).kind);
        currToken = *iterator;
        switch(currTokenKind){
            case NUMBER :
                currNodePtr->children.push_back(new Node(Token(NUMBER,currToken.value),currNodePtr));
                break;
            default:
                cerr<<"Expected return keyword"<<endl;
        }

        currNodePtr = (this->root->findChildByType(RETURN) != nullptr) ?
                        (this->root->findChildByType(RETURN)) : new Node();

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
                    break;
            }
        }
    }


    void print(){
        currNodePtr = root;
        queue<Node*> que;

        que.push(currNodePtr);
        cout<<"Printing"<<endl;
        while(!que.empty()){
            currNodePtr = que.front();
            que.pop();
            switch(currNodePtr->token.kind){
                case VARIABLE : 
                    cout<<"VARIABLE "<<(*symtab).indexToString(currNodePtr->token.value)<<" / ";
                    break;
                case NUMBER : 
                    cout<<"NUMBER "<<currNodePtr->token.value<<" / ";
                    break;
                case MAIN : 
                    cout<<"MAIN "<<" / ";
                    break;
                case RETURN : 
                    cout<<"RETURN "<<" / ";
                    break;
                default : 
                    cout<<"Default "<<currNodePtr->token.value<<" "<<currNodePtr->token.kind<<" / ";
            }
                cout<<"Node children size::"<<currNodePtr->children.size()<<endl;

            for(int i=0; i<currNodePtr->children.size(); i++){
                que.push((currNodePtr->children[i]));
            }

        }
        
    }


    Node* giveAccess(){
        return root;
    }
};