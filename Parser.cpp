//
// Created by Jared Tuck on 10/24/2021.
//
#include "Lexer.h"
#include "Parser.h"
#include <vector>

Block::Block(int D, linked_list* List){
    Depth = D; LIST = new linked_list(), Table = new SymTab();
    Scan4Stmt(LIST->split_set(1, LIST->listSize()-2));
    //Chops off first and las bracket of block and EOF.

}

Block::Block(int D, linked_list* List, SymTab* T){
    Depth = D; Table = new SymTab(); Table->prev = T;
    Scan4Stmt(LIST->split_set(1, LIST->listSize()-2));
    //Chops off first and las bracket of block and EOF.
}

void Block::StmtFound(linked_list* List, int POS){
    linked_list* B = List->split(POS);
    Stmt* S = new Stmt(B, Table, Depth+1);
    St.push_back(S);
}
Token* Block::Scan4Decl(linked_list* List){
    Token* temp = List->head;
    bool Ty, I, S;//Type, ID , Semicolon
    string ty, ID, Semi;
    for(int i=0;i<3; i++){
        if(i==0 && temp->get_class()=="BASE_TYPE"){ Ty=true;ty=temp->get_data();}
        if(i==1 && temp->get_class()=="id"){ I=true;ID=temp->get_data();}
        if(i==2 && temp->get_class()==";"){ S=true;};
        temp = temp->next;}
    if(Ty && I && S){
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
        int BR, BL = 0;
        bool B_EQ = true;
        temp = List->head;
        int pos = 0;
        while(temp->next){//scan until end of Stmt is found, check for decl at beginning of new search.
            if(pos==0){temp = Scan4Decl(List);}

            if(temp->get_class()=="BREAK" && pos==0){
                temp=temp->next->next;//Next tk should be ";" after break, need to error check for.
                linked_list* B = List->split(0);
                Stmt* S = new Stmt(B, Table, Depth+1);
                St.push_back(S);
                List->pop();//discard ";" after Break.
            }
            if(temp->get_data()=="{"){BR++;}
            if(temp->get_data()=="}"){BL++;}
            if(BR == BL){B_EQ = true;}else{B_EQ = false;}
            //^^^Determine if inside or outside of Brackets

            if(B_EQ && temp->get_data()=="}" && temp->next->get_class()=="ELSE"){StmtFound(List, pos);}else
            //^^^If Tok is a R.Bracket and Brackets match its the end of stmt unless followed by else.

            if(B_EQ && temp->get_data()==";"){StmtFound(List, pos);}else
            //^^^If Brackets are equal then semi colon signifies end of Stmt

            if(B_EQ && temp->next->get_data()=="if"){StmtFound(List, pos);}else
            //^^^If next next is a "if" then it signifies beginning of new stnt  therefore end of stmt found.

            if(B_EQ && temp->next->get_data()=="do"){StmtFound(List, pos);}else
            //^^^If next next is a "do" then it signifies beginning of new stnt  therefore end of stmt found.

            if(B_EQ && temp->next->get_data()=="for"){StmtFound(List, pos);}else
            //^^^If next next is a "for" then it signifies beginning of new stnt  therefore end of stmt found.
            {pos++;}
            //^^^ Nothing Found keep scanning
        }
        if(List->head && B_EQ){StmtFound(List, List->listSize()-1);}else{/*error state*/}
}