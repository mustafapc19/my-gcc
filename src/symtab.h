#include<iostream>
#include<vector>
#include "enums.h"

using namespace std;

#ifndef SYMTAB_H
#define SYMTAB_H

class SymTab{
private:
    vector<string> str;
    vector<int> value;
    vector<int> lvalueFlag;
    vector<TokenKind> tokenKind;
    int litCount;

public:
    SymTab(string s);

    SymTab();

    int push(string s);

    int push(string s, TokenKind tk);

    int size();

    string indexToString(int i);

    int indexToValue(int i);

    int getLitCount();

    int getLvalueFlag(int i);

    int isLvalueFlag(int i);

    int isRvalueFlag(int i);

    void setLvalueFlag(int i);

    void setRvalueFlag(int i);

    void setTokenKind(TokenKind tk,int i);

    TokenKind getTokenKind(int i);

    void print();

};

#endif