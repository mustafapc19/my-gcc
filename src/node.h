#include"token.h"

#ifndef NODE_H
#define NODE_H
class Node{
private:

public: 
    Token token;
    std::vector<Node*> children;
    Node* parent;

    Node(Token tok);

    Node(Token tok,Node* par);

    Node();

    bool operator==(Node nod);

    void changeToken(Token tok);

    void attachChild(Node* n);

    void attachParent(Node* n);

    Node* getParent();

    Node* findChildByType(int type);
};

#endif