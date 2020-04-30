#include<iostream>
#include<vector>
#include<iterator>

using namespace std;

class VarTab{
    public: 
    vector<string> varName;
    vector<TokenKind> varTokenKind;
    vector<int> stackOffset;

    VarTab(){

    }
    void push(string name,TokenKind tk,int sc){
        varName.push_back(name);
        varTokenKind.push_back(tk);
        stackOffset.push_back(sc);
    }
    int getIndexFromVarName(string name){
        for(int i = 0;i < varName.size();i++){
            if(name == varName[i]){ return i;}
        }
        return -1;
    }

    int getStackOffsetFromVarName(string name){
        for(int i = 0;i < varName.size();i++){
            if(name == varName[i]){ return stackOffset[i];}
        }
        return -1;
    }

    TokenKind getTokenKindFromIndex(int i){
        if(0 <= i && i < varName.size()){
            return varTokenKind[i];
        } else {
            cout << "VARTAB::Index access out of range"<<endl;
            return ERROR; 
        }
    }
    string getNameFromIndex(int i){
        if(0 <= i && i < varName.size()){
            return varName[i];
        } else {
            cout << "VARTAB::Index access out of range"<<endl;
            return " "; 
        }
    }

    void print(){
        for(int i=0; i<varName.size();i++){
            cout<<varName[i]<<" "<<stackOffset[i]<<" ";
            switch(varTokenKind[i]){
                case VARIABLE : 
                    cout << "VARIABLE ";
                    break;
                case NUMBER : 
                    cout << "NUMBER";
                    break;
                case VARIABLE_TYPE_CHAR:
                    cout << "VARIABLE_TYPE_CHAR";
                    break;
                case VARIABLE_TYPE_INT:
                    cout << "VARIABLE_TYPE_INT";
                    break;
                case LITERAL_STRING:
                    cout << "LITERAL_STRING";
                    break;
                default: 
                    cout << "VARTAB::print "<<varTokenKind[i];
            }
            cout<< endl;

        }
    }
};