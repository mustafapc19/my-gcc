#include"enums.h"
#ifndef VARTAB_H
#define VARTAB_H

class VarTab{
    public: 
    std::vector<std::string> varName;
    std::vector<TokenKind> varTokenKind;
    std::vector<int> stackOffset;

    VarTab();

    void push(std::string name,TokenKind tk,int sc);

    int getIndexFromVarName(std::string name);

    int getStackOffsetFromVarName(std::string name);

    TokenKind getTokenKindFromIndex(int i);

    std::string getNameFromIndex(int i);

    void print();

};

#endif