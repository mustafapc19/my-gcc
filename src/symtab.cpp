#include<iostream>
#include<vector>
#include"symtab.h"
#include"enums.h"
// #include<iterator>

using namespace std;

SymTab::SymTab(string s){
    str.push_back(s);
    value.push_back(0);
    lvalueFlag.push_back(0);
    tokenKind.push_back(VARIABLE);
    litCount = 0;
}

SymTab::SymTab(){
}

int SymTab::push(string s){
    for(int i=0;i<str.size();i++){
        if(str[i] == s){
            return i;
        }
    }
    str.push_back(s);
    value.push_back(0);
    lvalueFlag.push_back(0);
    tokenKind.push_back(VARIABLE);
    return str.size()-1;
}

int SymTab::push(string s, TokenKind tk){
    for(int i=0;i<str.size();i++){
        if(str[i] == s){
            return i;
        }
    }
    str.push_back(s);
    value.push_back(0);
    lvalueFlag.push_back(0);
    tokenKind.push_back(tk);
    return str.size()-1;
}

int SymTab::size(){
    return lvalueFlag.size();
}

string SymTab::indexToString(int i){
    if(0 <= i && i < str.size()){
        return str[i];
    } else {
        cout << "SYMTAB::Index access out of range"<<endl;
        return " "; 
    }
}

int SymTab::indexToValue(int i){
    if(0 <= i && i < str.size()){
        return value[i];
    } else {
        cout << "SYMTAB::Index access out of range"<<endl;
        return 0; 
    }
}

int SymTab::getLitCount(){
    return litCount;
}


int SymTab::getLvalueFlag(int i){
    if(0 <= i && i < str.size()){
        return lvalueFlag[i];
    } else {
        cout << "SYMTAB::Index access out of range"<<endl;
        return -2; 
    }
}


int SymTab::isLvalueFlag(int i){
    if(0 <= i && i < str.size()){
        return lvalueFlag[i]==1;
    } else {
        cout << "SYMTAB::Index access out of range"<<endl;
        return -2; 
    }
}

int SymTab::isRvalueFlag(int i){
    if(0 <= i && i < str.size()){
        return lvalueFlag[i]==-1;
    } else {
        cout << "SYMTAB::Index access out of range"<<endl;
        return -2; 
    }
}


void SymTab::setLvalueFlag(int i){
    if(0 <= i && i < str.size()){
        lvalueFlag[i] = 1;
    } else {
        cout << "SYMTAB::Index access out of range"<<endl;
        return; 
    }
}


void SymTab::setRvalueFlag(int i){
    if(0 <= i && i < str.size()){
        lvalueFlag[i] = -1;
    } else {
        cout << "SYMTAB::Index access out of range"<<endl;
        return; 
    }
}


void SymTab::setTokenKind(TokenKind tk,int i){
    if(0 <= i && i < str.size()){
        tokenKind[i] = tk;
    } else {
        cout << "SYMTAB::Index access out of range"<<endl;
        return; 
    }
}


TokenKind SymTab::getTokenKind(int i){
    if(0 <= i && i < str.size()){
        return tokenKind[i];
    } else {
        cout << "SYMTAB::Index access out of range"<<endl;
        return ERROR; 
    }
}


void SymTab::print(){
    for(int i=0; i<str.size();i++){
        cout<<str[i]<<" "<<lvalueFlag[i]<<" ";
        switch(tokenKind[i]){
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
                cout << "SYMTAB::print "<<tokenKind[i];
        }
        cout<< endl;
    }
}