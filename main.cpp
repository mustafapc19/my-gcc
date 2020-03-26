#include<iostream>
#include "enums.cpp"
#include "symtab.cpp"
#include "token.cpp"
#include "./AST.cpp"
#include "./lexer.cpp"

using namespace std;


int main(){
    SymTab symtab;
    // fstream sourceFile; 
    string sourceFileName; 
    
    sourceFileName = "file.txt"; 
    // sourceFile.open(sourceFileName.c_str()); 
  
    Lexer lexer(sourceFileName,&symtab);
    lexer.tokenList();
    AST ast(lexer.giveAccess(),&symtab);
    ast.print();
    // lexer.print();
    symtab.print();

    return 0; 
}