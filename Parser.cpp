//
// Created by Jared Tuck on 10/24/2021.
//
#include "Parser.h"
#include <vector>
Parser::Parser(Lexer* L){Lex=L;  Data = Lex->List; P = new Prog(Data);};

void Parser::PrintTree(){P->printProg();};

Block::Block(int D, linked_list* List){
    Depth = D; LIST=List; Table = new SymTab();
    Scan4Stmt(LIST->split_set(1, LIST->listSize()-2));
}

Block::Block(int D, linked_list* List, SymTab* T){
    cout<<"Block_Called"<<endl;
    Depth = D;
    LIST=List->split_set(1, List->listSize()-2);
    Table = new SymTab(T);
    Table->prev = T;
    Scan4Stmt(LIST);
}

void Block::StmtFound(linked_list* List, int POS){
    linked_list* B;
    int b =List->listSize();
    if(POS != List->listSize()-1){B = List->split(POS);}else{B=List;}
    B->Print();
    Stmt* S = new Stmt(B, Table, Depth+1+St.size());
    St.push_back(S);

}
Token* Block::Scan4Decl(linked_list* List){
    Token* temp = List->head;
    bool Ty=false, I=false, S=false;//Type, ID , Semicolon
    string ty, ID, Semi;
    for(int i=0;i<3; i++){
        if(i==0 && temp->get_class()=="BASE_TYPE"){ Ty=true;ty=temp->get_data();}
        if(i==1 && temp->get_class()=="ID"){ I=true;ID=temp->get_data();}
        if(i==2 && temp->get_class()==";"){ S=true;};
        temp = temp->next;}
    if(Ty && I && S){
        cout<<"Decl added "<<ty<<" "<<ID<< endl;
        List->pop();List->pop();List->pop();
        Table->push(ID,ty);
    }
    return List->head;
}
void Block::Scan4Stmt(linked_list* List){
    Token* temp = List->head;
    //   x assign | if (allexpr) stmt | if (allexpr) stmt else stmt | while (allexpr) stmt
    //    do stmt while (allexpr) ; | for (assign allexpr ; incdecexpr)  stmt  | x break ; | block
    int BR=0, BL = 0;
    bool B_EQ = true;
    int pos = 0;
    cout<<endl;
    while(temp){cout<<temp->get_class()<<" ";temp=temp->next;}
    cout<<endl;
    temp=List->head;
    string LOOK;
    while(temp){//scan until end of Stmt is found, check for decl at beginning of new search.
        int SZ = List->listSize();

        if(temp->next){LOOK = temp->next->get_class();}else{LOOK="";}

        while(pos==0 && temp->get_class()=="BASE_TYPE"){
            temp = Scan4Decl(List);
            while(temp){cout<<temp->get_class()<<" ";temp=temp->next;}
            cout<<endl;
            temp=List->head;
        }
        //cout<<temp->get_class()<<"  ";
        if(temp->get_class()=="BREAK" && pos==0){
            temp=temp->next->next;//Next tk should be ";" after break, need to error check for.
            linked_list* B = List->split(0);
            Stmt* S = new Stmt(B, Table, Depth);
            St.push_back(S);
            List->pop();//discard ";" after Break.
        }
        if(temp->get_data()=="}"){BR++;}
        if(temp->get_data()=="{"){BL++;}
        if(BR == BL){B_EQ = true;}else{B_EQ = false;}
        //^^^Determine if inside or outside of Brackets
        if(B_EQ && temp->get_data()=="}" && !temp->next){cout<<"*";temp=temp->next;StmtFound(List, pos);if(pos==SZ-1){break;} pos =0;}
        else//^^^If Tok is a R.Bracket and Brackets match its the end of stmt unless followed by else.
        if(B_EQ && temp->get_data()=="}" && LOOK!="ELSE"){cout<<"**";temp=temp->next;StmtFound(List, pos);if(pos==SZ-1){break;}pos =0;}
        else//^^^If Tok is a R.Bracket and Brackets match its the end of stmt unless followed by else.
        if(B_EQ && temp->get_data()==";"){cout<<"***";temp=temp->next;StmtFound(List, pos);if(pos==SZ-1){break;}pos=0;}
        else//^^^If Brackets are equal then semi colon signifies end of Stmt
        if(B_EQ && LOOK=="if"){cout<<"****";temp=temp->next;StmtFound(List, pos);if(pos==SZ-1){break;}pos=0;}
        else//^^^If next next is a "if" then it signifies beginning of new stnt  therefore end of stmt found.
        if(B_EQ && LOOK=="do"){cout<<"*****";temp=temp->next;StmtFound(List, pos);if(pos==SZ-1){break;}pos=0;}
        else//^^^If next next is a "do" then it signifies beginning of new stnt  therefore end of stmt found.
        if(B_EQ && LOOK=="for"){cout<<"******";temp=temp->next;StmtFound(List, pos);if(pos==SZ-1){break;}pos=0;}
        else//^^^If next next is a "for" then it signifies beginning of new stmt therefore end of stmt found.
        {pos++;temp=temp->next;}
        //^^^ Nothing Found keep scanning
        }
        //if(List->head && B_EQ){StmtFound(List, List->listSize()-1);}else{/*error state*/}
}
void Block::printBlock(){
    for(int i=0; i<Depth; i++){cout<<"| "; }
    cout<<"+--Block"<<endl;
    int SZ=St.size();
    for(int i=0;i<SZ;i++){
       // int j=0;while(j<i){cout<<"| ";j++;}
        St[i]->printStmt();
    }
};