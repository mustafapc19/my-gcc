#include<iostream>

using namespace std;

class Node{
    Token token;
    vector<Node> childNodeArray;

public:
    Node(Token t){
        this->token = t;
    }
    
    void pushChildNode(Node n){
        this->childNodeArray.push_back(n);
    }
}