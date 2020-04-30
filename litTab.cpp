#include<iostream>
#include<vector>
#include<iterator>

using namespace std;

class LitTab{
    public: 
    vector<string> litName;
    vector<string> litValue;

    LitTab(){

    }
    string push(string name,string sc){
        name = name + to_string(litName.size());
        litName.push_back(name);
        litValue.push_back(sc);
        return name;
    }
    int getIndexFromLitName(string name){
        for(int i = 0;i < litName.size();i++){
            if(name == litName[i]){ return i;}
        }
        return -1;
    }

    string getLitValueFromLitName(string name){
        for(int i = 0;i < litName.size();i++){
            if(name == litName[i]){ return litValue[i];}
        }
        return "";
    }

    string getNameFromIndex(int i){
        if(0 <= i && i < litName.size()){
            return litName[i];
        } else {
            cout << "VARTAB::Index access out of range"<<endl;
            return " "; 
        }
    }

    void print(){
        for(int i=0; i<litName.size();i++){
            cout<<litName[i]<<" "<<litValue[i]<<" ";
            cout<< endl;
        }
    }

    vector<string> finalPrint(){
        vector<string> vec;
        string str,tempStr;
        for(int i=0; i<litName.size();i++){
            tempStr = "";
            for(int j=0;j<litValue[i].size()-1;j++){
                if(litValue[i][j]=='\\' && litValue[i][j+1]=='n'){
                    j += 2;
                    tempStr += "\",10,";
                    if(j!=litValue[i].size()-3){ tempStr += "\"";}
                }
                tempStr += litValue[i][j];
                if(j == litValue[i].size()-2 && litValue[i][j] != '\\' && litValue[i][j+1] != 'n'){
                    tempStr +='"';
                }
            }
            str = litName[i]+":"+" db "+tempStr+ ",0";
            vec.push_back(str);
        }
        return vec;
    }
};