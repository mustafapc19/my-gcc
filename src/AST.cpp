#include<iostream>
#include<vector>
#include<iterator>
#include <cstdlib>
#include<queue>
#include"token.h"
#include"node.h"
// #include"token.h"

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
        vector<Token>::iterator peekIter = iterator;
        peekIter++;
        currTokenKind = (TokenKind)((*peekIter).kind);
        while(currTokenKind != BRACKET_CURLY_CLOSE){
            root = stmtDFA(root);
            peekIter = iterator;
            peekIter++;
            currTokenKind = (TokenKind)((*peekIter).kind);
        }

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
            case WHILE:
                tempNodePtr->attachChild(whileDFA(tempNodePtr));
                break;
            case IDENTIFIER_CHAR : 
                // tempNodePtr->attachChild(dataCharDFA(tempNodePtr));
                break;
            case IDENTIFIER_INT : 
                tempNodePtr->attachChild(dataIntDFA(tempNodePtr));
                break;
            case IDENTIFIER_STRING : 
                // tempNodePtr->attachChild(dataStringDFA(tempNodePtr));
                break;
            case VARIABLE:
                currTokenKind = symtab->getTokenKind(iterator->value);
                switch(currTokenKind){
                    case VARIABLE_TYPE_INT:
                        tempNodePtr->attachChild(varIntDFA(tempNodePtr));
                        break;
                    default:
                        cerr<<"AST::stmtDFA variable not defined before use"<<endl;
                }
                break;
            case PRINTF :
                tempNodePtr->attachChild(printfDFA(tempNodePtr));
                break;
            case SCANF :
                tempNodePtr->attachChild(scanfDFA(tempNodePtr));
                break;
            default: 
                cout<<"stmtDFA:: ";
                iterator->print(symtab);
        }

        return tempNodePtr;
    }

    Node* varIntDFA(Node* parentNodePtr){
        iterator++;
        if(iterator->kind != EQUAL){ cerr<<"AST::varIntDFA expected '='"<<endl;}
        Node* tempNodePtr = new Node(Token(EQUAL),parentNodePtr);
        iterator--;
        tempNodePtr->attachChild(new Node(Token(VARIABLE_TYPE_INT,iterator->value),tempNodePtr));
        iterator++;
        return exprDFA(tempNodePtr);
    }

    Node* scanfDFA(Node* parentNode){
        Node* tempNodePtr;
        tempNodePtr = new Node(Token(SCANF),parentNode);
        iterator++;
        currTokenKind = (TokenKind)((*iterator).kind);
        if(currTokenKind != BRACKET_SMALL_OPEN){ cerr<<"AST::printfDFA expected ("<<endl;}
        iterator++;
        currTokenKind = (TokenKind)((*iterator).kind);
        Token t = *iterator;
        while(currTokenKind != BRACKET_SMALL_CLOSE && currTokenKind != SEMICOLON){
            // cout<<"AST::printDFA ";
            t = *iterator;
            if(currTokenKind == COMMA) { 
                iterator++;
                currTokenKind = (TokenKind)((*iterator).kind);
                continue;
            }
            if(currTokenKind == AMPERSAND){
                iterator++;
                t = *iterator;
                if(t.kind != VARIABLE){cerr<<"AST::scandDFA expected var type after AMPERSAND"<<endl;t.print(symtab);}
                
                if(symtab->getTokenKind(t.value) == VARIABLE_TYPE_INT){t.kind = VARIABLE_TYPE_INT_AMPERSAND;}
                else{cerr<<"AST::scanfDFA only supports int :("<<endl;}
                tempNodePtr->attachChild(new Node(t,tempNodePtr));
                iterator++;
                currTokenKind = (TokenKind)(iterator->kind);
                continue;
            }
            tempNodePtr->attachChild(new Node(t,tempNodePtr));
            iterator++;
            currTokenKind = (TokenKind)(iterator->kind);

        }
        iterator++;
        return tempNodePtr;
    }


    Node* printfDFA(Node* parentNode){
        Node* tempNodePtr;
        tempNodePtr = new Node(Token(PRINTF),parentNode);
        iterator++;
        currTokenKind = (TokenKind)((*iterator).kind);
        if(currTokenKind != BRACKET_SMALL_OPEN){ cerr<<"AST::printfDFA expected ("<<endl;}
        iterator++;
        currTokenKind = (TokenKind)((*iterator).kind);
        Token t = *iterator;
        while(currTokenKind != BRACKET_SMALL_CLOSE && currTokenKind != SEMICOLON){
            // cout<<"AST::printDFA ";
            t = *iterator;
            if(currTokenKind == COMMA) { 
                iterator++;
                currTokenKind = (TokenKind)((*iterator).kind);
                continue;
            }
            tempNodePtr->attachChild(new Node(t,tempNodePtr));
            iterator++;
            currTokenKind = (TokenKind)(iterator->kind);

        }
        iterator++;
        return tempNodePtr;
    }

    Node* dataIntDFA(Node* parentNodePtr){
        Node* tempNodePtr;
        iterator++;
        currTokenKind = (TokenKind)((*iterator).kind);
        vector<Token>::iterator tmpIter = iterator;
        tmpIter++;
        switch(currTokenKind){
            case VARIABLE :
                if((TokenKind)tmpIter->kind == EQUAL){
                    symtab->setLvalueFlag(iterator->value);
                    symtab->setTokenKind(VARIABLE_TYPE_INT,iterator->value);
                    tempNodePtr = new Node(Token(EQUAL),parentNodePtr);
                    tempNodePtr->attachChild(new Node(Token(VARIABLE_TYPE_INT,iterator->value),tempNodePtr));
                    iterator++;
                    parentNodePtr = exprDFA(tempNodePtr);
                } else {
                    symtab->setLvalueFlag(iterator->value);
                    symtab->setTokenKind(VARIABLE_TYPE_INT,iterator->value);
                    // tempNodePtr = new Node(Token(VARIABLE_TYPE_INT,iterator->value),parentNodePtr);
                    tempNodePtr = new Node(Token(NONE,0),parentNodePtr);
                    iterator++;
                    if((TokenKind)iterator->kind != SEMICOLON){ cerr<< "AST::dataIntDFA expected ;"<<endl;}
                }
                
                break;
            default : 
                cerr<<"Expected return keywork"<<endl;
        }
        return tempNodePtr;
    }

    Node* returnDFA(Node* parentNodePtr){
        Node* tempNodePtr = new Node(Token(RETURN),parentNodePtr);
        return exprDFA(tempNodePtr);
    }
    
    Node* exprDFA(Node* parentNode){      //doesnt return a new node. Just the old one 
        iterator++;
        vector<Token>::iterator localIter = iterator;
        iterator++;
        currTokenKind = (TokenKind)((*iterator).kind);
        Node* localNode;
        switch(currTokenKind){
            case SEMICOLON:
                currTokenKind = (TokenKind)(localIter->kind);
                currTokenKind = (currTokenKind == VARIABLE) ? symtab->getTokenKind(localIter->value) 
                                                            : currTokenKind ;
                parentNode->attachChild(new Node(Token(currTokenKind,localIter->value),parentNode));
                break;
            case PLUS: 
                localNode = new Node(Token(PLUS),parentNode);
                currTokenKind = (TokenKind)localIter->kind;
                localNode->attachChild(new Node(Token(currTokenKind,localIter->value),localNode));
                iterator++;
                currTokenKind = (TokenKind)iterator->kind;
                localNode->attachChild(new Node(Token(currTokenKind,iterator->value),localNode));
                iterator++;
                if(iterator->kind != SEMICOLON){ cerr<<"AST::exprDFA expected semicolon"<<endl;}
                parentNode->attachChild(localNode);
                break;
            case MINUS: 
                localNode = new Node(Token(MINUS),parentNode);
                currTokenKind = (TokenKind)localIter->kind;
                localNode->attachChild(new Node(Token(currTokenKind,localIter->value),localNode));
                iterator++;
                currTokenKind = (TokenKind)iterator->kind;
                localNode->attachChild(new Node(Token(currTokenKind,iterator->value),localNode));
                iterator++;
                if(iterator->kind != SEMICOLON){ cerr<<"AST::exprDFA expected semicolon"<<endl;}
                parentNode->attachChild(localNode);
                break;
        }

        return parentNode;
    }

    /*Node* exprDFA(Node* parentNode){
        iterator++;
        currTokenKind = (TokenKind)((*iterator).kind);
        switch(currTokenKind){
            case NUMBER :
                parentNode->attachChild(new Node(Token(NUMBER,iterator->value),parentNode));
                break;
            default : 
                cerr<<"AST::exprDFA Expected the required keywork"<<endl;
        }
        iterator++;
        currTokenKind = (TokenKind)((*iterator).kind);
        if(currTokenKind != SEMICOLON){ cerr<<"AST::exprDFA Expected \";\""<<endl;}

        return parentNode;
    }*/

    Node* whileDFA(Node* parentNodePtr){
        Node* tempNodePtr = new Node(Token(WHILE),parentNodePtr);

        iterator++;
        currTokenKind = (TokenKind)((*iterator).kind);
        if(currTokenKind != BRACKET_SMALL_OPEN){ cerr<<"AST::whileDFA Expected '(' after while"<<endl; }

        tempNodePtr->attachChild(condDFA(tempNodePtr));
        
        iterator++;
        currTokenKind = (TokenKind)((*iterator).kind);
        if(currTokenKind != BRACKET_SMALL_CLOSE){ cerr<<"AST::whileDFA Expected ')' (while)"<<endl; }

        iterator++;
        currTokenKind = (TokenKind)((*iterator).kind);
        if(currTokenKind != BRACKET_CURLY_OPEN){ cerr<<"AST::whileDFA Expected '{' (while)"<<endl; }

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

    Node* ifDFA(Node* parentNodePtr){
        Node* tempNodePtr = new Node(Token(IF),parentNodePtr);

        iterator++;
        currTokenKind = (TokenKind)((*iterator).kind);
        if(currTokenKind != BRACKET_SMALL_OPEN){ cerr<<"AST::ifDFA Expected '(' after if"<<endl; }

        tempNodePtr->attachChild(condDFA(tempNodePtr));
        
        iterator++;
        currTokenKind = (TokenKind)((*iterator).kind);
        if(currTokenKind != BRACKET_SMALL_CLOSE){ cerr<<"AST::ifDFA Expected ')' (if)"<<endl; }

        iterator++;
        currTokenKind = (TokenKind)((*iterator).kind);
        if(currTokenKind != BRACKET_CURLY_OPEN){ cerr<<"AST::ifDFA Expected '{' (if)"<<endl; }

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
        Node* tempNodePtrChild;

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
                cerr<<"AST::condDFA Expected VAR or NUM(cond)"<<endl;
        }

        iterator++;
        currTokenKind = (TokenKind)((*iterator).kind);
        switch(currTokenKind){
            case EQUAL:
                iterator++;
                currTokenKind = (TokenKind)((*iterator).kind);
                switch(currTokenKind){
                    case EQUAL: 
                        tempNodePtrChild = new Node(Token(DOUBLE_EQUAL),tempNodePtr);
                        tempNodePtr->attachChild(tempNodePtrChild);
                        break;
                    default:
                        cerr<<"AST::condDFA Conditional operator incorrect(2)-";
                        iterator->print(symtab);
                        cerr<<endl;
                }
                break;
            case EXCLAIMATION:
                iterator++;
                currTokenKind = (TokenKind)((*iterator).kind);
                switch(currTokenKind){
                    case EQUAL: 
                        tempNodePtrChild = new Node(Token(NOT_EQUAL),tempNodePtr);
                        tempNodePtr->attachChild(tempNodePtrChild);
                        break;
                    default:
                        cerr<<"AST::condDFA Conditional operator incorrect(2)"<<endl;
                }
                break;
            default:
                cerr<<"AST::condDFA Conditional operator incorrect(1)"<<endl;
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
                cerr<<"AST::condDFA Expected VAR or NUM(cond)(2)"<<endl;
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
                case IDENTIFIER_INT :
                case IDENTIFIER_VOID:
                    nextTokenValue = (*symtab).indexToString((nextToken).value);
                    if( (TokenKind)(nextToken.kind) != VARIABLE || nextTokenValue != "main"){
                        cerr<<"AST::init ERROR : At WordIndex "<<iterator - tokenArray.begin()+1;
                        this->flag = 0;
                    }
                    break;
                case VARIABLE :
                    tokenValue = (*symtab).indexToString((currToken).value);
                    if((TokenKind)(nextToken.kind) != BRACKET_SMALL_OPEN || tokenValue != "main"){
                        cerr<<"AST::init ERROR : At WordIndex "<<iterator - tokenArray.begin()+1;
                        this->flag = 0;
                    }
                    break;
                case BRACKET_SMALL_OPEN:
                    if((TokenKind)(nextToken.kind) != BRACKET_SMALL_CLOSE){
                        cerr<<"AST::init ERROR : At WordIndex "<<iterator - tokenArray.begin()+1;
                        this->flag = 0;
                    }
                    break;
                case BRACKET_SMALL_CLOSE:
                    if((TokenKind)(nextToken.kind) != BRACKET_CURLY_OPEN){
                        cerr<<"AST::init ERROR : At WordIndex "<<iterator - tokenArray.begin()+1;
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
        cout<<endl<<endl<<"AST::Printing"<<endl;
        while(!que.empty()){
            currNodePtr = que.front();
            que.pop();
            // switch(currNodePtr->token.kind){
            currNodePtr->token.print(symtab);
            // }
            cout<<"Node children size::"<<currNodePtr->children.size()<<endl;

            for(int i=0; i<currNodePtr->children.size(); i++){
                que.push((currNodePtr->children[i]));
            }

            // cin>>test;
        }
        
    }


    Node* giveAccess(){
        if(root->children[root->children.size()-1]->token.kind!=RETURN){
            root->attachChild(new Node(Token(RETURN),root));
        }
        return root;
    }
};