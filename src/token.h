#include"symtab.h"
#ifndef TOKEN_H
#define TOKEN_H
class Token{
private:

public:
    int value;
    int kind;

    Token(int kind,int value);

    Token(int kind);

    Token();

    bool operator==(Token tok);

    void print(SymTab* symtab);
};

#endif