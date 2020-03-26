#include<iostream>
#include<vector>
// #include<iterator>

using namespace std;

class SymTab{
    vector<string> str;
    vector<int> value;

public:
    SymTab(string s){
        str.push_back(s);
        value.push_back(0);
    }
    SymTab(){

    }

    int push(string s){
        str.push_back(s);
        value.push_back(0);
        return str.size()-1;
    }

    string indexToString(int i){
        if(0 <= i && i < str.size()){
            return str[i];
        } else {
            cout << "SYMTAB::Index access out of range"<<endl;
            return " "; 
        }
    }
    int indexToValue(int i){
        return value[i];
    }

    void print(){
        for(int i=0; i<str.size();i++){
            cout<<str[i]<<" "<<value[i]<<endl;
        }
    }
};