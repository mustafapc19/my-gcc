#include<iostream>
#include<vector>
#include<iterator>
#include<sstream>
#include <string> 

using namespace std;

class Final{
    vector<string> finalCode;
    vector<string> interCode;
    LitTab litTab;
    VarTab varTab;
    int stackSize;
    int stackSizeMax;
    string varIdent;

public:

    Final(vector<string> code,SymTab* symtab,LitTab lt){
        interCode = code;
        litTab = lt;
        stackSize = 0;
        stackSizeMax = 1;
        varIdent = "__var_";
        for(int i = 0;i < symtab->size();i++){
            switch(symtab->getTokenKind(i)){
                // case LITERAL_STRING:
                //     litTab.push_back(symtab->indexToString(i));
                //     break;
                case VARIABLE_TYPE_INT:
                    stackSize += 4;
                    varTab.push(symtab->indexToString(i),symtab->getTokenKind(i),stackSize);
                    break;
                default:
                    break;
            }
        }

        do{
            stackSizeMax++;
        }while((int)(stackSize-1)/((16*stackSizeMax)) != 0);
        // stackSizeMax--;
        stackSizeMax *= 16;
        string str;
        std::stringstream sstream;
        sstream << std::hex << stackSizeMax;
        str = "0x"+sstream.str();

        finalCode.push_back("extern printf");
        finalCode.push_back("extern scanf");

        finalCode.push_back("SECTION .DATA");
        vector<string> secData = litTab.finalPrint();
        finalCode.insert(finalCode.end(),secData.begin(),secData.end());

        finalCode.push_back("SECTION .TEXT");
        finalCode.push_back("global main");
        finalCode.push_back("main:");

        size_t index;
        int lowIndex = 0;
        int highIndex = 0;
        interCode[2] += str;
        string tempVarName;
        for(int i=0;i< interCode.size(); i++){
            index = interCode[i].find(varIdent);
            // cout<<"TEST "<<lowIndex<<endl;
            if (index == std::string::npos) {
                finalCode.push_back(interCode[i]);
                continue;
            }
            lowIndex = static_cast<int>(index);

            str = "";
            tempVarName = "";
            for(int j=0;j<lowIndex;j++){
                str += interCode[i][j];
            }
            lowIndex +=varIdent.size();
            highIndex = lowIndex;
            while(interCode[i][lowIndex]!=',' && interCode[i][lowIndex]!=' ' && lowIndex<interCode[i].size()){
                tempVarName += interCode[i][lowIndex];
                lowIndex++;
            }
            sstream.str("");
            sstream << std::hex << varTab.getStackOffsetFromVarName(tempVarName);
            //TODO
            tempVarName = "[rbp-0x"+sstream.str()+"]";
            str += tempVarName;

            while(lowIndex<interCode[i].size()){
                str += interCode[i][lowIndex];
                lowIndex++;
            }
            // cout<<"TEST "<<lowIndex<<endl;
            finalCode.push_back(str);
        }




    }


    void print(){
        cout<<endl<<endl;

        for(int i=0;i<finalCode.size();i++){
            cout<<finalCode[i]<<endl;
        }
        cout<<endl<<"VARTAB"<<endl;
        varTab.print();
    }

    vector<string> getFinalCode(){
        return finalCode;
    }
};
