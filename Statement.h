//
// Created by Jared Tuck on 10/24/2021.
//

#ifndef INC_125PROJ_STATEMENT_H
#define INC_125PROJ_STATEMENT_H
#include "linked_list.h"
#include "SymTab.h"
#include "Stmt.h"


class Block;
class Stmt{
public:
    Stmt(linked_list* list, SymTab* T, int D){sTable = T; Depth = D; LIST = list; }
    linked_list* LIST;
    SymTab* sTable;
    int Depth;
    Stmt1* S1;
    Stmt2* S2;
    Stmt3* S3;
    Stmt4* S4;
    Stmt5* S5;
    Stmt6* S6;
    Block* B;
    Token* BREAK;
    //ADAM
    void makeNewStmt(linked_list list);//Determine type of statement and locate its endpoint.
};



void Stmt::makeNewStmt(linked_list* list){

    Token* temp = list->head;
    bool found_flag = false;
    int lbrack = 0;
    int rbrack = 0;

    //S2 & S3 Parsing
    if(temp->get_class() == "IF"){
        temp = temp->next;
        while (temp){
            if(temp->get_data() == "{"){
                lbrack++;
                while(lbrack != rbrack && lbrack != 0){

                    if(temp->get_data() == "{")
                        lbrack++;

                    if(temp->get_data() == "}")
                        rbrack++;

                    temp = temp->next;
                }
                temp = temp->next;

                if(temp->get_class() == "ELSE"){
                    S3 = new Stmt3(LIST, sTable, Depth+1);
                    found_flag = true;
                    break;
                }
            }
        }


        //If no Else is found, S2
        if(!found_flag)
            S2 = new Stmt2(LIST, sTable, Depth+1);

        //S4 Parsing
        if(temp->get_class() == "WHILE")
            S4 = new Stmt4(LIST, sTable, Depth+1);


        //S5 Parsing
        if(temp->get_class() == "DO")
            S5 = new Stmt5(LIST, sTable, Depth+1);

        //S6 Parsing
        if(temp->get_class() == "FOR")
            S6 = new Stmt6(LIST, sTable, Depth+1);


        //S1 parsing
        if(temp->get_class() == "ID")
            S1 = new Stmt1(LIST, sTable, Depth+1);


        if(temp->get_data() == "{")
            B = new Block(Depth+1, sTable);

        temp = list->head;
    }
#endif //INC_125PROJ_STATEMENT_H
