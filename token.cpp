#include<iostream>

using namespace std;


class Token{
public : 
    int value;
    int kind;


    Token(int kind,int value){
        this->value = value;
        this->kind = kind;
    }

    Token(int kind){
        this->value = 0;
        this->kind = kind;
    }

    Token(){
        this->value = 0;
        this->kind = 0;
    }

    void print(){
        cout<<"T-Kind-"<<(this->kind)<<"-Value-"<<(this->value)<<endl;
    }
};