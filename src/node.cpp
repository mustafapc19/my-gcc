#include<iostream>
#include<iterator>
#include"token.h"
#include"node.h"

using namespace std;



Node::Node(Token tok){
    this->token = tok;
    this->parent = nullptr;
}

Node::Node(Token tok,Node* par){
    this->token = tok;
    this->parent = par;
}

Node::Node(){
    this->token.kind = -1;
    this->token.value = 0;
    this->parent = nullptr;
}

bool Node::operator==(Node nod){
    return (this->token.value ==nod.token.value && this->token.kind == nod.token.kind && this->parent == nod.parent);
}

void Node::changeToken(Token tok){
    this->token.kind = tok.kind;
    this->token.value = tok.value;
}

void Node::attachChild(Node* n){
    this->children.push_back(n);
}

void Node::attachParent(Node* n){
    this->parent = n;
}

Node* Node::getParent(){
    return this->parent;
}

Node* Node::findChildByType(int type){
    for(vector<Node*>::iterator iter = children.begin(); iter != children.end(); iter++){
        if((*(*iter)).token.kind == type){
            return (*iter);
        }
    }
    return nullptr;
}
