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
        vector<string> stmtTemp;
        switch(currTokenKind){
            case RETURN : 
                stmtTemp = retDFA(currNodePtr);
                localInter.insert(localInter.end(),stmtTemp.begin(),stmtTemp.end());
                break;
            case EQUAL : 
                // cerr<<"YEAH";
                stmtTemp = equalDFA(currNodePtr);
                localInter.insert(localInter.end(),stmtTemp.begin(),stmtTemp.end());
                break; 
            case NONE:
                break;
            default : 
                cerr<<"Inter::stmtDFA default case Token ";
                currNodePtr->token.print();
                break;
        }
        return localInter;
    }

    vector<string> equalDFA(Node* currNodePtr){
        //check if children[0] is an lvalue
        if(!(symtab->isLvalueFlag(currNodePtr->children[0]->token.value))){ 
            cerr<<"Variable ";
            cerr<<symtab->indexToString(currNodePtr->children[0]->token.value);
            cerr<<" is not defined"<<endl;
        }

        vector<string> vec;
        vector<string> equalExprTemp;
        string str;
        TokenKind currTokenKind = (TokenKind)currNodePtr->children[0]->token.kind;
        switch(currTokenKind){
            case VARIABLE_TYPE_INT:
                equalExprTemp = exprDFA(currNodePtr->children[1]);
                vec.insert(vec.end(),equalExprTemp.begin(),equalExprTemp.end());
                str = "mov var_"+
                            symtab->indexToString(currNodePtr->children[0]->token.value)
                            +",eax";
                vec.push_back(str);
                break;
            default:
                cerr<<"INTER::equalDFA unknown variable type"<<endl;
        }

        return vec;        
    }

    vector<string> exprDFA(Node* currNodePtr){
        vector<string> vec;
        string str;
        TokenKind currTokenKind = (TokenKind)currNodePtr->token.kind;
        switch(currTokenKind){
            case PLUS:
                currTokenKind = (TokenKind)currNodePtr->children[0]->token.kind;
                str = currTokenKind == NUMBER ? to_string(currNodePtr->children[0]->token.value)
                                                : "var_"+
                                                    symtab->indexToString(currNodePtr->children[0]->token.value);
                str = "mov edx,"+str;
                vec.push_back(str);

                currTokenKind = (TokenKind)currNodePtr->children[1]->token.kind;
                str = currTokenKind == NUMBER ? to_string(currNodePtr->children[1]->token.value)
                                                : "var_"+
                                                    symtab->indexToString(currNodePtr->children[1]->token.value);
                str = "mov eax,"+str;
                vec.push_back(str);
                vec.push_back("add eax,edx");
                break;
            case MINUS:
                currTokenKind = (TokenKind)currNodePtr->children[0]->token.kind;
                str = currTokenKind == NUMBER ? to_string(currNodePtr->children[0]->token.value)
                                                : "var_"+
                                                    symtab->indexToString(currNodePtr->children[0]->token.value);
                str = "mov edx,"+str;
                vec.push_back(str);

                currTokenKind = (TokenKind)currNodePtr->children[1]->token.kind;
                str = currTokenKind == NUMBER ? to_string(currNodePtr->children[1]->token.value)
                                                : "var_"+
                                                    symtab->indexToString(currNodePtr->children[1]->token.value);
                str = "mov eax,"+str;
                vec.push_back(str);
                vec.push_back("sub eax,edx");
                break;
        }
        return vec;
    }

    vector<string> retDFA(Node* currNodePtr){
        vector<string> vec;
        string str;
        int val;
        currTokenKind = (TokenKind)currNodePtr->children[0]->token.kind;
        switch(currTokenKind){
            case NUMBER :
                val = currNodePtr->children[0]->token.value;
                str = "mov rax,"+to_string(val);
                vec.push_back(str);
                break;
            case VARIABLE_TYPE_INT :
                str = "mov rax, var_"+symtab->indexToString(currNodePtr->children[0]->token.value);
                vec.push_back(str);
                break;
            default:
                cerr<<"Inter::retDFA expected NUMBER(token)"<<endl;
                currNodePtr->children[0]->token.print();
        }
        str = "ret";
        vec.push_back(str);
        return vec;
    }

    void print(){
        cout<<endl<<endl;

        for(int i=0;i<interCode.size();i++){
            cout<<interCode[i]<<endl;
        }
    }


};