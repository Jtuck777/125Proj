//
// Created by Jared Tuck on 10/24/2021.
//
#include "Parser.h"
#include <vector>
Parser::Parser(Lexer* L){Lex=L;  Data = Lex->List;cout<<"Flag2"<<endl; P = new Prog(Data);};

void Parser::PrintTree(){std::cout<<"Print Tree";};

Block::Block(int D, linked_list* List){
    Depth = D; LIST=List; Table = new SymTab();
    Scan4Stmt(LIST->split_set(1, LIST->listSize()-2));
}

Block::Block(int D, linked_list* List, SymTab* T){
    cout<<"Block_Called"<<endl;
    Depth = D;
    LIST=List->split_set(1, List->listSize()-2);
    Table = new SymTab();
    Table->prev = T;
    Scan4Stmt(LIST);
    //Chops off first and las bracket of block;
}

void Block::StmtFound(linked_list* List, int POS){
    linked_list* B;
    //B = List->split_set(0,POS);
    if(POS != List->listSize()-1){B = List->split(POS);}else{B=List;}
    Stmt* S = new Stmt(B, Table, Depth+1);
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
        cout<<"Decl added"<<endl;
        List->pop();List->pop();List->pop();
        Decl* TEMP = new Decl(ty,ID);
        Table->push(TEMP);
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
        if(pos==0 && temp->get_class()=="BASE_TYPE"){temp = Scan4Decl(List);}
        //cout<<temp->get_class()<<"  ";
        if(temp->get_class()=="BREAK" && pos==0){
            temp=temp->next->next;//Next tk should be ";" after break, need to error check for.
            linked_list* B = List->split(0);
            Stmt* S = new Stmt(B, Table, Depth+1);
            St.push_back(S);
            List->pop();//discard ";" after Break.
        }
        if(temp->get_data()=="}"){BR++;}
        if(temp->get_data()=="{"){BL++;}
        if(BR == BL){B_EQ = true;}else{B_EQ = false;}
        //^^^Determine if inside or outside of Brackets
        if(B_EQ && temp->get_data()=="}" && !temp->next){temp=temp->next;StmtFound(List, pos);if(pos==SZ-1){break;} pos =0;}
        else//^^^If Tok is a R.Bracket and Brackets match its the end of stmt unless followed by else.
        if(B_EQ && temp->get_data()=="}" && LOOK!="ELSE"){temp=temp->next;StmtFound(List, pos);if(pos==SZ-1){break;}pos =0;}
        else//^^^If Tok is a R.Bracket and Brackets match its the end of stmt unless followed by else.
        if(B_EQ && temp->get_data()==";"){temp=temp->next;StmtFound(List, pos);if(pos==SZ-1){break;}pos=0;}
        else//^^^If Brackets are equal then semi colon signifies end of Stmt
        if(B_EQ && LOOK=="if"){temp=temp->next;StmtFound(List, pos);if(pos==SZ-1){break;}pos=0;}
        else//^^^If next next is a "if" then it signifies beginning of new stnt  therefore end of stmt found.
        if(B_EQ && LOOK=="do"){temp=temp->next;StmtFound(List, pos);if(pos==SZ-1){break;}pos=0;}
        else//^^^If next next is a "do" then it signifies beginning of new stnt  therefore end of stmt found.
        if(B_EQ && LOOK=="for"){temp=temp->next;StmtFound(List, pos);if(pos==SZ-1){break;}pos=0;}
        else//^^^If next next is a "for" then it signifies beginning of new stmt therefore end of stmt found.
        {pos++;temp=temp->next;}
        //^^^ Nothing Found keep scanning
        }
        //if(List->head && B_EQ){StmtFound(List, List->listSize()-1);}else{/*error state*/}
}