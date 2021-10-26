#ifndef INC_125PROJ_PARSER_H
#define INC_125PROJ_PARSER_H
#include <vector>
#include "Lexer.h"
#include "Statement.h"
#include "SymTab.h"
#include "Decl.h"

//Block object should pass a complete statement into stmt class
//Class will determine what type of stmt it is, create a new stmt depending on type.

class Block{
    friend class linked_list;
public:
    Block(int D){Depth = D; Table = new SymTab();};
    Block(int D, SymTab* T){Depth = D; Table = new SymTab(); Table->prev = T;}
    std::vector<Stmt> St;
    SymTab* Table;
    int Depth;
    void Scan4Stmt_Decl(linked_list* List){
        linked_list* T = List->split_set(1, List->listSize()-1);
        Token* temp = T->head;
        bool Ty, I, S;//Type, ID , Semicolon
        string ty, ID, Semi;
        for(int i=0;i<3; i++){
            if(i==0 && temp->get_class()=="BASE_TYPE"){ Ty=true;ty=temp->get_data();}
            if(i==1 && temp->get_class()=="id"){ I=true;ID=temp->get_data();}
            if(i==2 && temp->get_class()==";"){ S=true;};
            temp = temp->next;}
        if(Ty && I && S){
            T->pop();T->pop();T->pop();
            Decl* TEMP = new Decl(ty,ID);
            Table->push(TEMP);
            Scan4Stmt_Decl(T);
        }
        else
        {

        }
    };
    void printBlock();
};

class Prog{
public:
    Prog(){B= new Block(1);}
    Block* B;
    int Depth = 0;
    void PrintProg();
};

class Parser{
public:
    Parser(Lexer* L){Lex=L; Data = Lex->List;};
    Lexer* Lex;
    linked_list* Data;
    void PrintTree();

};


#endif //INC_125PROJ_PARSER_H

