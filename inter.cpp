#include<iostream>
#include<vector>
#include<iterator>

using namespace std;

class Inter{
    Node* root;
    SymTab* symtab;
    // Node* currNodePtr;
    vector<string> interCode;
    TokenKind currTokenKind;
    Token currToken;

public:

    Inter(Node* nl,SymTab* st){
        root = nl;
        symtab = st;
        init(root);
    }

    void init(Node* currNodePtr){
        currTokenKind = (TokenKind)currNodePtr->token.kind;
        if(currTokenKind != MAIN){ cerr<<"INTER:: Token MAIN expected"<<endl;}
        else {
            interCode.push_back("push rbp");
            for(int i = 0;i < currNodePtr->children.size(); i++){
                vector<string> stmtTemp = stmtDFA(currNodePtr->children[i]);
                interCode.insert(interCode.end(),stmtTemp.begin(),stmtTemp.end());
            }
        }
    }

    vector<string> stmtDFA(Node* currNodePtr){
        currTokenKind = (TokenKind)currNodePtr->token.kind;
        vector<string> localInter;
        switch(currTokenKind){
            case RETURN : 
                vector<string> stmtTemp = retDFA(currNodePtr);
                localInter.insert(localInter.end(),stmtTemp.begin(),stmtTemp.end());
                break;
            // default : 
            //     cerr<<"Inter::stmtDFA default case";
            //     break;
        }
        return localInter;
    }

    vector<string> retDFA(Node* currNodePtr){
        currTokenKind = (TokenKind)currNodePtr->children[0]->token.kind;
        if(currTokenKind != NUMBER){ cerr<<"Inter::retDFA expected NUMBER(token)";}
        int val = currNodePtr->children[0]->token.value;
        string str = "mov rax,"+to_string(val);
        vector<string> vec;
        vec.push_back(str);
        return vec;
    }

    void print(){
        for(int i=0;i<interCode.size();i++){
            cout<<interCode[i]<<endl;
        }
    }


};