#include<iostream>
#include<vector>
#include<iterator>
#include"litTab.h"

using namespace std;


LitTab::LitTab(){
}

string LitTab::push(string name,string sc){
    name = name + to_string(litName.size());
    litName.push_back(name);
    litValue.push_back(sc);
    return name;
}

int LitTab::getIndexFromLitName(string name){
    for(int i = 0;i < litName.size();i++){
        if(name == litName[i]){ return i;}
    }
    return -1;
}

string LitTab::getLitValueFromLitName(string name){
    for(int i = 0;i < litName.size();i++){
        if(name == litName[i]){ return litValue[i];}
    }
    return "";
}

string LitTab::getNameFromIndex(int i){
    if(0 <= i && i < litName.size()){
        return litName[i];
    } else {
        cout << "VARTAB::Index access out of range"<<endl;
        return " "; 
    }
}

void LitTab::print(){
    for(int i=0; i<litName.size();i++){
        cout<<litName[i]<<" "<<litValue[i]<<" ";
        cout<< endl;
    }
}

vector<string> LitTab::finalPrint(){
    vector<string> vec;
    string str,tempStr;
     tempStr = "";
     for(int i=0; i<litName.size();i++){
         vector<string> tmp;
         tempStr = "";
         for(int j=0;j<litValue[i].size()-1;j++){
             if(litValue[i][j]=='\\' && litValue[i][j+1]=='n'){
                 if(tempStr!=""){tmp.push_back(tempStr);}
                 j += 1;
                 tempStr = "10";
                 tmp.push_back(tempStr);
                 tempStr = "";
             }  
             else if(litValue[i][j]!='"'){tempStr+=litValue[i][j];}
         }
         if(tempStr != ""){tmp.push_back(tempStr);}
         tempStr = "";
         for(int j=0;j<tmp.size();j++){
             str = tmp[j];
             // cerr<<"liTab::finalPrint "<<str<<endl;
            if(tmp[j]!="10"){tempStr +="\"" + str +"\"";}
            else { tempStr += "10";}
            tempStr += ",";
        }
        tempStr +="0";
        tempStr =  litName[i]+":"+" db "+tempStr;
        vec.push_back(tempStr);
    }
    return vec;
}
