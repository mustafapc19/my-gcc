#include<iostream>
#include<iterator>

using namespace std;


class Token{
public : 
    int value;
    int kind;


    Token(int kind,int value){
        this->value = value;
        this->kind = kind;
    }

    Token(int kind){
        this->value = 0;
        this->kind = kind;
    }

    Token(){
        this->value = 0;
        this->kind = -1;
    }
    
    /* operator=(Token tok){
        this->value = tok.value;
        this->kind = tok.kind;
    } */

    bool operator==(Token tok){
        return (this->value == tok.value && this->kind == tok.kind);
    }

    void print(){
        cout<<"T-Kind-"<<(this->kind)<<"-Value-"<<(this->value)<<endl;
    }
};


class Node{
public: 
    Token token;
    vector<Node*> children;

    Node(Token tok){
        this->token = tok;
    }

    Node(){
        this->token.kind = -1;
        this->token.value = 0;
    }

    void changeToken(Token tok){
        this->token.kind = tok.kind;
        this->token.value = tok.value;
    }

    void attachChild(Node* n){
        this->children.push_back(n);
    }

    /* Node findChildByToken(Token tok){
        for(vector<Token>::iterator iter=this->children.begin(); iter != this->children.end();iter++){
            if(*iter == *tok){
                return tok;
            }
        }
        else {
            return Token(-1,-1);
    } */
};


