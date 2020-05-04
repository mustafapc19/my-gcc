#include<iostream>
#include<vector>
#include<iterator>
#include"token.h"
#include"node.h"
#include"litTab.h"

using namespace std;

class Inter{
    Node* root;
    SymTab* symtab;
    // Node* currNodePtr;
    vector<string> interCode;
    TokenKind currTokenKind;
    Token currToken;
    int litCount;
    LitTab litTab;
    string litIdent;
    string varIdent;
    string ifIdent;
    string loopIdent;
    int ifCount;
    int loopCount;

public:

    Inter(Node* nl,SymTab* st){
        root = nl;
        symtab = st;
        litCount = 0;
        ifCount = 0;
        loopCount = 0;
        litIdent = "__lit_";
        varIdent = "__var_";
        ifIdent = "__if_";
        loopIdent = "__loop_";
        init(root);
    }

    void init(Node* currNodePtr){
        currTokenKind = (TokenKind)currNodePtr->token.kind;
        if(currTokenKind != MAIN){ cerr<<"INTER:: Token MAIN expected"<<endl;}
        else {
            interCode.push_back("push rbp");
            interCode.push_back("mov rbp,rsp");
            interCode.push_back("sub rsp,");
            for(int i = 0;i < currNodePtr->children.size(); i++){
                vector<string> stmtTemp = stmtDFA(currNodePtr->children[i]);
                interCode.insert(interCode.end(),stmtTemp.begin(),stmtTemp.end());
            }
        }
    }

    vector<string> stmtDFA(Node* currNodePtr){
        currTokenKind = (TokenKind)currNodePtr->token.kind;
        vector<string> localInter;
        vector<string> stmtTemp;
        switch(currTokenKind){
            case RETURN : 
                stmtTemp = retDFA(currNodePtr);
                localInter.insert(localInter.end(),stmtTemp.begin(),stmtTemp.end());
                break;
            case EQUAL : 
                // cerr<<"YEAH";
                stmtTemp = equalDFA(currNodePtr);
                localInter.insert(localInter.end(),stmtTemp.begin(),stmtTemp.end());
                break;
            case PRINTF:
                stmtTemp = printfDFA(currNodePtr);
                localInter.insert(localInter.end(),stmtTemp.begin(),stmtTemp.end());
                break;
            case SCANF:
                stmtTemp = scanfDFA(currNodePtr);
                localInter.insert(localInter.end(),stmtTemp.begin(),stmtTemp.end());
                break;
            case IF: 
                stmtTemp = ifDFA(currNodePtr);
                localInter.insert(localInter.end(),stmtTemp.begin(),stmtTemp.end());
                break;
            case WHILE: 
                stmtTemp = whileDFA(currNodePtr);
                localInter.insert(localInter.end(),stmtTemp.begin(),stmtTemp.end());
                break;
            case NONE:
                break;
            default : 
                cerr<<"Inter::stmtDFA default case Token ";
                currNodePtr->token.print(symtab);
                break;
        }
        return localInter;
    }

    vector<string> whileDFA(Node* currNodePtr){
        vector<string> vec;
        vector<string> tmp;
        int localLoopCount = loopCount;
        loopCount++;

        vec.push_back(loopIdent+to_string(localLoopCount)+"start"+":"+" nop");
        tmp = whileCondDFA(currNodePtr->children[0],localLoopCount,loopIdent);
        vec.insert(vec.end(),tmp.begin(),tmp.end());
        for(int i = 1;i < currNodePtr->children.size(); i++){
                // cerr<<"INTER::ifDFA ";
                // currNodePtr->children[i]->token.print(symtab);
                vector<string> stmtTemp = stmtDFA(currNodePtr->children[i]);
                vec.insert(vec.end(),stmtTemp.begin(),stmtTemp.end());
        }
        vec.push_back("jmp "+loopIdent+to_string(localLoopCount)+"start");
        vec.push_back(loopIdent+to_string(localLoopCount)+"end"+":"+" nop");
        return vec;
    }

    vector<string> whileCondDFA(Node* currNodePtr,int localLabelCount,string labelIdent){
        vector<string> vec;
        TokenKind currTokenKind = (TokenKind)currNodePtr->children[1]->token.kind;
        Node* localNodePtr = currNodePtr;
        switch(currTokenKind){
            case DOUBLE_EQUAL:
                if(localNodePtr->children[0]->token.kind == NUMBER){
                    vec.push_back("mov edx,"+to_string(localNodePtr->children[0]->token.value));
                } 
                else if(symtab->getTokenKind(localNodePtr->children[0]->token.value) == VARIABLE_TYPE_INT){
                    vec.push_back("mov edx,"+varIdent+symtab->indexToString(localNodePtr->children[0]->token.value));
                } 
                else{
                    cerr<<"INTER::condDFA unexpected token-";
                    localNodePtr->children[0]->token.print(symtab);
                }

                if(localNodePtr->children[2]->token.kind == NUMBER){
                    vec.push_back("mov ecx,"+to_string(localNodePtr->children[2]->token.value));
                } 
                else if(symtab->getTokenKind(localNodePtr->children[2]->token.value) == VARIABLE_TYPE_INT){
                    vec.push_back("mov ecx,"+varIdent+symtab->indexToString(localNodePtr->children[2]->token.value));
                }
                else{
                    cerr<<"INTER::condDFA unexpected token-";
                    localNodePtr->children[2]->token.print(symtab);
                }

                vec.push_back("cmp edx,ecx");
                vec.push_back("jne "+labelIdent+to_string(localLabelCount)+"end");
                break;
            case NOT_EQUAL:
                if(localNodePtr->children[0]->token.kind == NUMBER){
                    vec.push_back("mov edx,"+to_string(localNodePtr->children[0]->token.value));
                } 
                else if(symtab->getTokenKind(localNodePtr->children[0]->token.value) == VARIABLE_TYPE_INT){
                    vec.push_back("mov edx,"+varIdent+symtab->indexToString(localNodePtr->children[0]->token.value));
                }
                else{
                    cerr<<"INTER::condDFA unexpected token-";
                    localNodePtr->children[0]->token.print(symtab);
                }

                if(localNodePtr->children[2]->token.kind == NUMBER){
                    vec.push_back("mov ecx,"+to_string(localNodePtr->children[0]->token.value));
                } 
                else if(symtab->getTokenKind(localNodePtr->children[2]->token.value) == VARIABLE_TYPE_INT){
                    vec.push_back("mov ecx,"+varIdent+symtab->indexToString(localNodePtr->children[0]->token.value));
                }
                else{
                    cerr<<"INTER::condDFA unexpected token-";
                    localNodePtr->children[2]->token.print(symtab);
                }

                vec.push_back("cmp edx,ecx");
                vec.push_back("je "+labelIdent+to_string(localLabelCount)+"end");
                break;
            default : 
                cerr<<"INTER::condDFA Incorrect operator";
                currNodePtr->children[0]->token.print(symtab);
        }
        return vec;

    }

    vector<string> ifDFA(Node* currNodePtr){
        vector<string> vec;
        vector<string> tmp;
        int localIfCount = ifCount;
        ifCount++;

        tmp = ifCondDFA(currNodePtr->children[0],localIfCount,ifIdent);
        vec.insert(vec.end(),tmp.begin(),tmp.end());
        for(int i = 1;i < currNodePtr->children.size(); i++){
                // cerr<<"INTER::ifDFA ";
                // currNodePtr->children[i]->token.print(symtab);
                vector<string> stmtTemp = stmtDFA(currNodePtr->children[i]);
                vec.insert(vec.end(),stmtTemp.begin(),stmtTemp.end());
        }
        vec.push_back(ifIdent+to_string(localIfCount)+":"+" nop");
        return vec;
    }

    vector<string> ifCondDFA(Node* currNodePtr,int localLabelCount,string labelIdent){
        vector<string> vec;
        TokenKind currTokenKind = (TokenKind)currNodePtr->children[1]->token.kind;
        Node* localNodePtr = currNodePtr;
        switch(currTokenKind){
            case DOUBLE_EQUAL:
                if(localNodePtr->children[0]->token.kind == NUMBER){
                    vec.push_back("mov edx,"+to_string(localNodePtr->children[0]->token.value));
                } 
                else if(symtab->getTokenKind(localNodePtr->children[0]->token.value) == VARIABLE_TYPE_INT){
                    vec.push_back("mov edx,"+varIdent+symtab->indexToString(localNodePtr->children[0]->token.value));
                } 
                else{
                    cerr<<"INTER::condDFA unexpected token-";
                    localNodePtr->children[0]->token.print(symtab);
                }

                if(localNodePtr->children[2]->token.kind == NUMBER){
                    vec.push_back("mov ecx,"+to_string(localNodePtr->children[2]->token.value));
                } 
                else if(symtab->getTokenKind(localNodePtr->children[2]->token.value) == VARIABLE_TYPE_INT){
                    vec.push_back("mov ecx,"+varIdent+symtab->indexToString(localNodePtr->children[2]->token.value));
                }
                else{
                    cerr<<"INTER::condDFA unexpected token-";
                    localNodePtr->children[2]->token.print(symtab);
                }

                vec.push_back("cmp edx,ecx");
                vec.push_back("jne "+labelIdent+to_string(localLabelCount));
                break;
            case NOT_EQUAL:
                if(localNodePtr->children[0]->token.kind == NUMBER){
                    vec.push_back("mov edx,"+to_string(localNodePtr->children[0]->token.value));
                } 
                else if(symtab->getTokenKind(localNodePtr->children[0]->token.value) == VARIABLE_TYPE_INT){
                    vec.push_back("mov edx,"+varIdent+symtab->indexToString(localNodePtr->children[0]->token.value));
                }
                else{
                    cerr<<"INTER::condDFA unexpected token-";
                    localNodePtr->children[0]->token.print(symtab);
                }

                if(localNodePtr->children[2]->token.kind == NUMBER){
                    vec.push_back("mov ecx,"+to_string(localNodePtr->children[0]->token.value));
                } 
                else if(symtab->getTokenKind(localNodePtr->children[2]->token.value) == VARIABLE_TYPE_INT){
                    vec.push_back("mov ecx,"+varIdent+symtab->indexToString(localNodePtr->children[0]->token.value));
                }
                else{
                    cerr<<"INTER::condDFA unexpected token-";
                    localNodePtr->children[2]->token.print(symtab);
                }

                vec.push_back("cmp edx,ecx");
                vec.push_back("je "+labelIdent+to_string(localLabelCount));
                break;
            default : 
                cerr<<"INTER::condDFA Incorrect operator";
                currNodePtr->children[0]->token.print(symtab);
        }
        return vec;

    }

    vector<string> scanfDFA(Node* currNodePtr){
        vector<string> vec;
        TokenKind currTokenKind = (TokenKind)currNodePtr->children[0]->token.kind;
        if(currTokenKind != LITERAL_STRING){ cerr<<"INTER::scanfDFA expected literal string in 1st arg"<<endl;}
        string name = litTab.push(litIdent,symtab->indexToString(currNodePtr->children[0]->token.value));
        string str;
        str = "mov rdi,"+name;
        vec.push_back(str);

        vector<string> regs = { "rsi","rdx","rcx","r8","r9"};
        for(int i=1;i<currNodePtr->children.size();i++){
            TokenKind currTokenKind = (TokenKind)currNodePtr->children[i]->token.kind;
            currTokenKind = currTokenKind == NUMBER ? NUMBER 
                                                    : symtab->getTokenKind(currNodePtr->children[i]->token.value);
            switch(currTokenKind){
                case NUMBER:
                    if(i>regs.size()){ cerr<<"INTER::printfDFA regs count less"<<endl;}
                    str = "lea "+regs[i-1]+","+to_string(currNodePtr->children[i]->token.value);
                    vec.push_back(str);
                    break;
                case VARIABLE_TYPE_INT:
                    if(i>regs.size()){ cerr<<"INTER::printfDFA regs count less"<<endl;}
                    str = "lea "+regs[i-1]+","+varIdent+symtab->indexToString(currNodePtr->children[i]->token.value);
                    vec.push_back(str);
                    break;
                default:
                    cerr<<"INTER::scanfDFA wrong argument type "<<endl;
                    currNodePtr->children[i]->token.print(symtab);
            }
        }
        vec.push_back("mov rax,0");
        vec.push_back("call scanf");

        return vec;
    }

    vector<string> printfDFA(Node* currNodePtr){
        vector<string> vec;
        TokenKind currTokenKind = (TokenKind)currNodePtr->children[0]->token.kind;
        if(currTokenKind != LITERAL_STRING){ cerr<<"INTER::printfDFA expected literal string in 1st arg"<<endl;}
        string name = litTab.push(litIdent,symtab->indexToString(currNodePtr->children[0]->token.value));
        string str;
        str = "mov rdi,"+name;
        vec.push_back(str);

        vector<string> regs = { "rsi","rdx","rcx","r8d","r9d"};
        for(int i=1;i<currNodePtr->children.size();i++){
            TokenKind currTokenKind = (TokenKind)currNodePtr->children[i]->token.kind;
            currTokenKind = currTokenKind == NUMBER ? NUMBER 
                                                    : symtab->getTokenKind(currNodePtr->children[i]->token.value);
            switch(currTokenKind){
                case NUMBER:
                    if(i>regs.size()){ cerr<<"INTER::printfDFA regs count less"<<endl;}
                    str = "mov "+regs[i-1]+","+to_string(currNodePtr->children[i]->token.value);
                    vec.push_back(str);
                    break;
                case VARIABLE_TYPE_INT:
                    if(i>regs.size()){ cerr<<"INTER::printfDFA regs count less"<<endl;}
                    str = "mov "+regs[i-1]+","+varIdent+symtab->indexToString(currNodePtr->children[i]->token.value);
                    vec.push_back(str);
                    break;
                default:
                    cerr<<"INTER::printfDFA wrong argument type "<<endl;
                    currNodePtr->children[i]->token.print(symtab);
            }
        }
        vec.push_back("mov rax,0");
        vec.push_back("call printf");

        return vec;
    }

    vector<string> equalDFA(Node* currNodePtr){
        //check if children[0] is an lvalue
        if(!(symtab->isLvalueFlag(currNodePtr->children[0]->token.value))){ 
            cerr<<"Variable ";
            cerr<<symtab->indexToString(currNodePtr->children[0]->token.value);
            cerr<<" is not defined"<<endl;
        }

        vector<string> vec;
        vector<string> equalExprTemp;
        string str;
        TokenKind currTokenKind = (TokenKind)currNodePtr->children[0]->token.kind;
        switch(currTokenKind){
            case VARIABLE_TYPE_INT:
                equalExprTemp = exprDFA(currNodePtr->children[1]);
                vec.insert(vec.end(),equalExprTemp.begin(),equalExprTemp.end());
                str = "mov __var_"+
                            symtab->indexToString(currNodePtr->children[0]->token.value)
                            +",eax";
                vec.push_back(str);
                break;
            default:
                cerr<<"INTER::equalDFA unknown variable type"<<endl;
        }

        return vec;        
    }

    vector<string> exprDFA(Node* currNodePtr){
        vector<string> vec;
        string str;
        TokenKind currTokenKind = (TokenKind)currNodePtr->token.kind;
        switch(currTokenKind){
            case PLUS:
                currTokenKind = (TokenKind)currNodePtr->children[0]->token.kind;
                str = currTokenKind == NUMBER ? to_string(currNodePtr->children[0]->token.value)
                                                : "__var_"+
                                                    symtab->indexToString(currNodePtr->children[0]->token.value);
                str = "mov edx,"+str;
                vec.push_back(str);

                currTokenKind = (TokenKind)currNodePtr->children[1]->token.kind;
                str = currTokenKind == NUMBER ? to_string(currNodePtr->children[1]->token.value)
                                                : "__var_"+
                                                    symtab->indexToString(currNodePtr->children[1]->token.value);
                str = "mov eax,"+str;
                vec.push_back(str);
                vec.push_back("add eax,edx");
                break;
            case MINUS:
                currTokenKind = (TokenKind)currNodePtr->children[0]->token.kind;
                str = currTokenKind == NUMBER ? to_string(currNodePtr->children[0]->token.value)
                                                : "__var_"+
                                                    symtab->indexToString(currNodePtr->children[0]->token.value);
                str = "mov edx,"+str;
                vec.push_back(str);

                currTokenKind = (TokenKind)currNodePtr->children[1]->token.kind;
                str = currTokenKind == NUMBER ? to_string(currNodePtr->children[1]->token.value)
                                                : "__var_"+
                                                    symtab->indexToString(currNodePtr->children[1]->token.value);
                str = "mov eax,"+str;
                vec.push_back(str);
                vec.push_back("sub eax,edx");
                break;
            case NUMBER:
                str = "mov eax,"+to_string(currNodePtr->token.value);
                vec.push_back(str);
                break;
        }
        return vec;
    }

    vector<string> retDFA(Node* currNodePtr){
        vector<string> vec;
        string str;
        int val;
        if(currNodePtr->children.size()){
          currTokenKind = (TokenKind)currNodePtr->children[0]->token.kind;
            switch(currTokenKind){
                case NUMBER :
                    val = currNodePtr->children[0]->token.value;
                    str = "mov rax,"+to_string(val);
                    vec.push_back(str);
                    break;
                case VARIABLE_TYPE_INT :
                    str = "mov rax, __var_"+symtab->indexToString(currNodePtr->children[0]->token.value);
                    vec.push_back(str);
                    break;
                default:
                    cerr<<"Inter::retDFA expected NUMBER(token)"<<endl;
                    currNodePtr->children[0]->token.print(symtab);
            }  
        } else {
            
        }
        
        str = "leave";
        vec.push_back(str);
        str = "ret";
        vec.push_back(str);
        return vec;
    }

    LitTab getLitTab(){
        return litTab;
    }

    vector<string> getInterCode(){
        return interCode;
    }

    void print(){
        cout<<endl<<endl;

        for(int i=0;i<interCode.size();i++){
            cout<<interCode[i]<<endl;
        }
    }


};