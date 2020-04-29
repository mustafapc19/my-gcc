#include<iostream>
#include<vector>
// #include<iterator>

using namespace std;

class SymTab{
    vector<string> str;
    vector<int> value;
    vector<int> lvalueFlag;
    vector<TokenKind> tokenKind;
    int litCount;

public:
    SymTab(string s){
        str.push_back(s);
        value.push_back(0);
        lvalueFlag.push_back(0);
        tokenKind.push_back(VARIABLE);
        litCount = 0;
    }
    SymTab(){

    }

    int push(string s){
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

    int push(string s, TokenKind tk){
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

    string indexToString(int i){
        if(0 <= i && i < str.size()){
            return str[i];
        } else {
            cout << "SYMTAB::Index access out of range"<<endl;
            return " "; 
        }
    }
    int indexToValue(int i){
        if(0 <= i && i < str.size()){
            return value[i];
        } else {
            cout << "SYMTAB::Index access out of range"<<endl;
            return 0; 
        }
    }

    int getLitCount(){
        return litCount;
    }

    int getLvalueFlag(int i){
        if(0 <= i && i < str.size()){
            return lvalueFlag[i];
        } else {
            cout << "SYMTAB::Index access out of range"<<endl;
            return -2; 
        }
    }

    int isLvalueFlag(int i){
        if(0 <= i && i < str.size()){
            return lvalueFlag[i]==1;
        } else {
            cout << "SYMTAB::Index access out of range"<<endl;
            return -2; 
        }
    }

    int isRvalueFlag(int i){
        if(0 <= i && i < str.size()){
            return lvalueFlag[i]==-1;
        } else {
            cout << "SYMTAB::Index access out of range"<<endl;
            return -2; 
        }
    }

    void setLvalueFlag(int i){
        if(0 <= i && i < str.size()){
            lvalueFlag[i] = 1;
        } else {
            cout << "SYMTAB::Index access out of range"<<endl;
            return; 
        }
    }

    void setRvalueFlag(int i){
        if(0 <= i && i < str.size()){
            lvalueFlag[i] = -1;
        } else {
            cout << "SYMTAB::Index access out of range"<<endl;
            return; 
        }
    }

    void setTokenKind(TokenKind tk,int i){
        if(0 <= i && i < str.size()){
            tokenKind[i] = tk;
        } else {
            cout << "SYMTAB::Index access out of range"<<endl;
            return; 
        }
    }

    TokenKind getTokenKind(int i){
        if(0 <= i && i < str.size()){
            return tokenKind[i];
        } else {
            cout << "SYMTAB::Index access out of range"<<endl;
            return ERROR; 
        }
    }

    void print(){
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
};