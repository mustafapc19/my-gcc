#include<iostream>
#include "enums.cpp"
#include "symtab.cpp"
#include "tokenAndNode.cpp"
#include "./AST.cpp"
#include "./lexer.cpp"
#include "./inter.cpp"

using namespace std;


int main(){
    SymTab symtab;
    string sourceFileName; 
    
    sourceFileName = "file.txt"; 
  
    Lexer lexer(sourceFileName,&symtab);
    lexer.tokenList();
    AST ast(lexer.giveAccess(),&symtab);
    ast.print();
    Inter inter(ast.giveAccess(),&symtab);
    // lexer.print();
    inter.print();
    symtab.print();

    return 0; 
}