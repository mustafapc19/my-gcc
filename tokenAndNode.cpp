#include<iostream>
#include<iterator>

using namespace std;


class Token{
public : 
    int value;
    int kind;


    Token(int kind,int value){
        this->value = value;
        this->kind = kind;
    }

    Token(int kind){
        this->value = 0;
        this->kind = kind;
    }

    Token(){
        this->value = 0;
        this->kind = -1;
    }
    
    /* operator=(Token tok){
        this->value = tok.value;
        this->kind = tok.kind;
    } */

    bool operator==(Token tok){
        return (this->value == tok.value && this->kind == tok.kind);
    }

    void print(){
        TokenKind tokenKind = (TokenKind)this->kind;
        switch(tokenKind){
            case VARIABLE : 
                cerr<<"VARIABLE "<<(symtab).indexToString(this->value)<<" / ";
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
                cerr<<"VARIABLE_TYPE_INT NAME "<<(symtab).indexToString(this->value)<<" VALUE "<<(symtab).indexToValue(this->value)<<" / ";
                break;
            }
            case VARIABLE_TYPE_INT_AMPERSAND : {
                cerr<<"VARIABLE_TYPE_INT_AMPERSAND NAME "<<(symtab).indexToString(this->value)<<" VALUE "<<(symtab).indexToValue(this->value)<<" / ";
                break;
            }
            case IDENTIFIER_STRING : {
                cerr<<"STRING "<<" / ";
                break;
            }
            case LITERAL_STRING : {
                cerr<<"LITERAL_STRING "<<(symtab).indexToString(this->value)<<" / ";
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
        // cerr<<"T-Kind-"<<(this->kind)<<"-Value-"<<(this->value)<<endl;
    }
};
// VARIABLE,
//     NUMBER,
//     BRACKET_SMALL_OPEN,
//     BRACKET_SMALL_CLOSE,
//     BRACKET_CURLY_OPEN,
//     BRACKET_CURLY_CLOSE,
//     SEMICOLON,
//     EQUAL,
//     IDENTIFIER_INT,
//     IDENTIFIER_VOID,
//     RETURN,
//     MAIN,
//     IF,
//     COND,
//     DOUBLE_EQUAL,
//     PLUS,
//     MINUS

class Node{
public: 
    Token token;
    vector<Node*> children;
    Node* parent;

    Node(Token tok){
        this->token = tok;
        this->parent = nullptr;
    }

    Node(Token tok,Node* par){
        this->token = tok;
        this->parent = par;
    }

    Node(){
        this->token.kind = -1;
        this->token.value = 0;
        this->parent = nullptr;
    }

    bool operator==(Node nod){
        return (this->token.value ==nod.token.value && this->token.kind == nod.token.kind && this->parent == nod.parent);
    }

    void changeToken(Token tok){
        this->token.kind = tok.kind;
        this->token.value = tok.value;
    }

    void attachChild(Node* n){
        this->children.push_back(n);
    }

    void attachParent(Node* n){
        this->parent = n;
    }

    Node* getParent(){
        return this->parent;
    }

    Node* findChildByType(int type){
        for(vector<Node*>::iterator iter = children.begin(); iter != children.end(); iter++){
            if((*(*iter)).token.kind == type){
                return (*iter);
            }
        }
        return nullptr;
    }

    /* Node findChildByToken(Token tok){
        for(vector<Token>::iterator iter=this->children.begin(); iter != this->children.end();iter++){
            if(*iter == *tok){
                return tok;
            }
        }
        else {
            return Token(-1,-1);
    } */
};


