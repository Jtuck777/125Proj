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
    Stmt(linked_list list, SymTab* T, int D){sTable = T; Depth = D; LIST = list; }
    linked_list LIST;
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
#endif //INC_125PROJ_STATEMENT_H
