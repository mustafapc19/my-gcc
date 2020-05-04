using namespace std;

#ifndef LITTAB_H
#define LITTAB_H

class LitTab{
public: 
    vector<string> litName;
    vector<string> litValue;

    LitTab();

    string push(string name,string sc);

    int getIndexFromLitName(string name);

    string getLitValueFromLitName(string name);

    string getNameFromIndex(int i);

    void print();

    vector<string> finalPrint();
};

#endif