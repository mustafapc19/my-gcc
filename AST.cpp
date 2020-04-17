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
        iterator--;
        root = new Node();
        root->changeToken(Token(MAIN,0));
        root = stmtDFA(root);

    }
    

    Node* stmtDFA(Node* parentNode){
        Node* tempNodePtr = parentNode;
        iterator++;
        currTokenKind = (TokenKind)((*iterator).kind);
        switch(currTokenKind){
            case RETURN :
                tempNodePtr->attachChild(returnDFA(tempNodePtr));
                break;
            case IF : 
                tempNodePtr->attachChild(ifDFA(tempNodePtr));
                break;
            default: 
                cout<<"stmtDFA:: "<<currTokenKind;
        }

        return tempNodePtr;
    }

    Node* returnDFA(Node* parentNodePtr){
        Node* tempNodePtr = new Node(Token(RETURN),parentNodePtr);
        return exprDFA(tempNodePtr);
    }

    Node* exprDFA(Node* parentNode){
        iterator++;
        currTokenKind = (TokenKind)((*iterator).kind);
        switch(currTokenKind){
            case NUMBER :
                parentNode->attachChild(new Node(Token(NUMBER,iterator->value),parentNode));
                break;
            default : 
                cerr<<"Expected return keywork"<<endl;
        }
        iterator++;
        currTokenKind = (TokenKind)((*iterator).kind);
        if(currTokenKind != SEMICOLON){ cerr<<"Expected \";\""<<endl;}

        return parentNode;
    }


    Node* ifDFA(Node* parentNodePtr){
        Node* tempNodePtr = new Node(Token(IF),parentNodePtr);

        iterator++;
        currTokenKind = (TokenKind)((*iterator).kind);
        if(currTokenKind != BRACKET_SMALL_OPEN){ cerr<<"Expected '(' after if"<<endl; }

        tempNodePtr->attachChild(condDFA(tempNodePtr));
        
        iterator++;
        currTokenKind = (TokenKind)((*iterator).kind);
        if(currTokenKind != BRACKET_SMALL_CLOSE){ cerr<<"Expected ')' (if)"<<endl; }

        iterator++;
        currTokenKind = (TokenKind)((*iterator).kind);
        if(currTokenKind != BRACKET_CURLY_OPEN){ cerr<<"Expected '{' (if)"<<endl; }

        iterator++;
        currTokenKind = (TokenKind)((*iterator).kind);
        while(currTokenKind != BRACKET_CURLY_CLOSE){
            iterator--;
            // tempNodePtr->attachChild(stmtDFA(tempNodePtr));
            tempNodePtr = stmtDFA(tempNodePtr);
            iterator++;
            currTokenKind = (TokenKind)((*iterator).kind);
        }
        // cout<<"IF::iter.kind:"<<iterator->kind<<" iter.value:"<<iterator->value<<endl;

        return tempNodePtr;
    }

    Node* condDFA(Node* parentNodePtr){
        Node* tempNodePtr = new Node(Token(COND),parentNodePtr);

        iterator++;
        currTokenKind = (TokenKind)((*iterator).kind);
        switch(currTokenKind){
            case VARIABLE : 
                tempNodePtr->attachChild(new Node(Token(VARIABLE,iterator->value),tempNodePtr));
                break;
            case NUMBER : 
                tempNodePtr->attachChild(new Node(Token(NUMBER,iterator->value), tempNodePtr));
                break;
            default :
                cerr<<"Expected VAR or NUM(cond)"<<endl;
        }

        iterator++;
        currTokenKind = (TokenKind)((*iterator).kind);
        switch(currTokenKind){
            case EQUAL:
                iterator++;
                currTokenKind = (TokenKind)((*iterator).kind);
                switch(currTokenKind){
                    case EQUAL: 
                        tempNodePtr->attachChild(new Node(Token(DOUBLE_EQUAL),tempNodePtr));
                        break;
                    default:
                        cerr<<"Conditional operator incorrect(2)"<<endl;
                }
                break;
            default:
                cerr<<"Conditional operator incorrect(1)"<<endl;
        }

        iterator++;
        currTokenKind = (TokenKind)((*iterator).kind);
        switch(currTokenKind){
            case VARIABLE : 
                tempNodePtr->attachChild(new Node(Token(VARIABLE,iterator->value),tempNodePtr));
                break;
            case NUMBER : 
                tempNodePtr->attachChild(new Node(Token(NUMBER,iterator->value), tempNodePtr));
                break;
            default :
                cerr<<"Expected VAR or NUM(cond)(2)"<<endl;
        }

        return tempNodePtr;
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
                        cerr<<"ERROR : At WordIndex "<<iterator - tokenArray.begin()+1;
                        this->flag = 0;
                    }
                    break;
                case VARIABLE :
                    tokenValue = (*symtab).indexToString((currToken).value);
                    if((TokenKind)(nextToken.kind) != BRACKET_SMALL_OPEN || tokenValue != "main"){
                        cerr<<"ERROR : At WordIndex "<<iterator - tokenArray.begin()+1;
                        this->flag = 0;
                    }
                    break;
                case BRACKET_SMALL_OPEN:
                    if((TokenKind)(nextToken.kind) != BRACKET_SMALL_CLOSE){
                        cerr<<"ERROR : At WordIndex "<<iterator - tokenArray.begin()+1;
                        this->flag = 0;
                    }
                    break;
                case BRACKET_SMALL_CLOSE:
                    if((TokenKind)(nextToken.kind) != BRACKET_CURLY_OPEN){
                        cerr<<"ERROR : At WordIndex "<<iterator - tokenArray.begin()+1;
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
        char test;

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
                case IF : 
                    cout<<"IF "<<" / ";
                    break;
                case DOUBLE_EQUAL : 
                    cout<<"== "<<" / ";
                    break;
                case COND : 
                    cout<<"cond "<<" / ";
                    break;
                default : 
                    cout<<"Default "<<currNodePtr->token.value<<" "<<currNodePtr->token.kind<<" / ";
            }
                cout<<"Node children size::"<<currNodePtr->children.size()<<endl;

            for(int i=0; i<currNodePtr->children.size(); i++){
                que.push((currNodePtr->children[i]));
            }

            // cin>>test;
        }
        
    }


    Node* giveAccess(){
        return root;
    }
};