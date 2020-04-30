#include<iostream>
#include<fstream>
#include "enums.cpp"
#include "symtab.cpp"
SymTab symtab;
#include "tokenAndNode.cpp"
#include "./varTab.cpp"
#include "./litTab.cpp"
#include "./AST.cpp"
#include "./lexer.cpp"
#include "./inter.cpp"
#include "./final.cpp"

using namespace std;


int main(){
    string sourceFileName; 
    vector<string> finalCode;
    
    sourceFileName = "file.txt"; 
  
    Lexer lexer(sourceFileName,&symtab);
    lexer.tokenList();
    // lexer.print();
    AST ast(lexer.giveAccess(),&symtab);
    // ast.print();
    // cerr<<endl;
    Inter inter(ast.giveAccess(),&symtab);
    // inter.print();
    // symtab.print();
    Final final(inter.getInterCode(),&symtab,inter.getLitTab());
    // final.print();
    finalCode = final.getFinalCode();
    ofstream myfile;
    myfile.open("asm.asm",ios::trunc);
    for(int i=0;i<finalCode.size();i++){
        myfile<<finalCode[i]<<endl;
    }
    myfile.close();
    // system("./my-gcc");
    system("nasm asm.asm -f elf64 -o my-prog.o");
    system("gcc -no-pie -g my-prog.o");

    return 0; 
}