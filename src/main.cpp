#include<iostream>
#include<fstream>
#include "symtab.h"
#include "./AST.cpp"
#include "./lexer.cpp"
#include "./inter.cpp"
#include "./final.cpp"

using namespace std;


int main(int argc, char** argv){
    string sourceFileName; 
    vector<string> finalCode;
    sourceFileName = ""; 
    SymTab symtab;
    
    sourceFileName = argv[1];
  
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
    system("nasm asm.asm -f elf64 -o my-prog.o");
    system("gcc -no-pie -g my-prog.o");

    return 0; 
}