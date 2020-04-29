#include<iostream>
#include "enums.cpp"
#include "symtab.cpp"
SymTab symtab;
#include "tokenAndNode.cpp"
#include "./AST.cpp"
#include "./lexer.cpp"
#include "./inter.cpp"

using namespace std;


int main(){
    string sourceFileName; 
    
    sourceFileName = "file.txt"; 
  
    Lexer lexer(sourceFileName,&symtab);
    lexer.tokenList();
    lexer.print();
    AST ast(lexer.giveAccess(),&symtab);
    ast.print();
    cerr<<endl;
    Inter inter(ast.giveAccess(),&symtab);
    inter.print();
    symtab.print();

    return 0; 
}