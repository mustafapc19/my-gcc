#include<iostream>
#include<iterator>
#include "token.h"
#include "enums.h"
#include "symtab.h"

using namespace std;

Token::Token(int kind,int value){
    this->value = value;
    this->kind = kind;
}

Token::Token(int kind){
    this->value = 0;
    this->kind = kind;
}

Token::Token(){
    this->value = 0;
    this->kind = -1;
}

bool Token::operator==(Token tok){
    return (this->value == tok.value && this->kind == tok.kind);
}

void Token::print(SymTab* symtab){
    TokenKind tokenKind = (TokenKind)this->kind;
    switch(tokenKind){
        case VARIABLE : 
            cerr<<"VARIABLE "<<(*symtab).indexToString(this->value)<<" / ";
            break;
        case NUMBER : 
            cerr<<"NUMBER "<<this->value<<" / ";
            break;
        case BRACKET_CURLY_OPEN : {
            cerr<<"{ "<<" / ";
            break;
        }
        case BRACKET_CURLY_CLOSE : {
            cerr<<"} "<<" / ";
            break;
        }
        case BRACKET_SMALL_OPEN : {
            cerr<<"( "<<" / ";
            break;
        }
        case BRACKET_SMALL_CLOSE : {
            cerr<<") "<<" / ";
            break;
        }
        case SEMICOLON : {
            cerr<<"; "<<" / ";
            break;
        }
        case EQUAL : {
            cerr<<"= "<<" / ";
            break;
        }
        case EXCLAIMATION : {
            cerr<<"! "<<" / ";
            break;
        }
        case IDENTIFIER_INT : {
            cerr<<"IDENTIFIER_INT "<<" / ";
            break;
        }
        case IDENTIFIER_VOID : {
            cerr<<"DATATYPE VOID "<<" / ";
            break;
        }
        case IDENTIFIER_CHAR : {
            cerr<<"DATATYPE CHAR "<<" / ";
            break;
        }
        case VARIABLE_TYPE_CHAR : {
            cerr<<"VARIABLE_TYPE_CHAR "<<(char)this->value<<" / ";
            break;
        }
        case VARIABLE_TYPE_INT : {
            cerr<<"VARIABLE_TYPE_INT NAME "<<(*symtab).indexToString(this->value)<<" VALUE "<<(*symtab).indexToValue(this->value)<<" / ";
            break;
        }
        case VARIABLE_TYPE_INT_AMPERSAND : {
            cerr<<"VARIABLE_TYPE_INT_AMPERSAND NAME "<<(*symtab).indexToString(this->value)<<" VALUE "<<(*symtab).indexToValue(this->value)<<" / ";
            break;
        }
        case IDENTIFIER_STRING : {
            cerr<<"STRING "<<" / ";
            break;
        }
        case LITERAL_STRING : {
            cerr<<"LITERAL_STRING "<<(*symtab).indexToString(this->value)<<" / ";
            break;
        }
        case PLUS : {
            cerr<<"+ "<<" / ";
            break;
        }
        case MINUS : {
            cerr<<"- "<<" / ";
            break;
        }
        case COMMA : {
            cerr<<", "<<" / ";
            break;
        }
        case MAIN : 
            cerr<<"MAIN "<<" / ";
            break;
        case RETURN : 
            cerr<<"RETURN "<<" / ";
            break;
        case PRINTF : 
            cerr<<"PRINTF "<<" / ";
            break;
        case SCANF :
            cerr<<"SCANF "<<" / ";
            break;
        case IF : 
            cerr<<"IF "<<" / ";
            break;
        case WHILE :
            cerr<<"WHILE "<<" / ";
            break;
        case DOUBLE_EQUAL : 
            cerr<<"== "<<" / ";
            break;
        case NOT_EQUAL : 
            cerr<<"!= "<<" / "; 
            break ;
        case COND : 
            cerr<<"COND "<<" / ";
            break;
        case NONE : 
            cerr<<"NONE "<<" / ";
            break;
        case AMPERSAND:
            cerr<<"& "<<" / ";
            break;
        default : 
            cerr<<"Token::Default "<<this->value<<" "<<this->kind<<" / ";
    }
}