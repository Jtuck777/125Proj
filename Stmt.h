//
// Created by Jared Tuck on 10/24/2021.
//

#ifndef INC_125PROJ_STMT_H
#define INC_125PROJ_STMT_H

#include "linked_list.h"
#include "SymTab.h"
#include "MiscClass.h"


class Stmt;

class Stmt1{
    //Assign
public:
    Stmt1();
    Stmt1(linked_list list, SymTab* T, int D){ sTable = T; Depth = D;}
    int Depth;
    SymTab* sTable;
    Token* ID;
    allexpr* allExpression;
    void printStmt1(); //Prints "|" according to depth, and the corresponding components. ID, allexpr.

};
////////////////////////////////////////////////////////////////////
class Stmt2{
    //if(allexpr)stmt
public:
    Stmt2(linked_list list, SymTab* T, int D)
    {sTable = T, Depth = D; LIST = list;
    allExpression = FindALLexpr(LIST, sTable, Depth);
    S1 = FindStmt(LIST, sTable, Depth);}
    linked_list LIST;
    int Depth;
    SymTab* sTable;
    Token* IF;
    allexpr* allExpression;
    Stmt* S1;
    allexpr* FindALLexpr(linked_list list, SymTab* T, int D);
    Stmt* FindStmt(linked_list list, SymTab* T, int D);
    void printStmt2();
};
///////////////////////////////////////////////////////////////////
class Stmt3{
    //if(allexpr) stmt else stmt
    public:
    Stmt3(linked_list list, SymTab* T, int D){sTable = T, Depth = D;LIST=list;}
    linked_list LIST;
    int Depth;
    SymTab* sTable;
    allexpr* allExpresion;
    Token* IF;
    Stmt* S1;
    Token* ELSE;
    Stmt* S2;
    void printStmt3();
};
////////////////////////////////////////////////////////////////////
class Stmt4{
    //while(allexpr)stmt
public:
    Stmt4(linked_list list, SymTab* T, int D){sTable = T, Depth = D;LIST=list;}
    linked_list LIST;
    int Depth;
    SymTab* sTable;
    Token* While;
    allexpr* allExression;
    Stmt* S1;
    void printStmt4();
};
////////////////////////////////////////////////////////////////////
class Stmt5{
    //do stmt while(allexpression);
public:
    Stmt5(linked_list list, SymTab* T, int D){sTable = T, Depth = D;LIST=list;}
    linked_list LIST;
    int Depth;
    SymTab* sTable;
    Token* DO;
    Stmt* S1;
    Token* WHILE;
    allexpr* allExpression;
    void printStmt5();
};
//////////////////////////////////////////////////////////////////////
class Stmt6{
    //for(assign allexpr; incdecexpr) stmt
public:
    Stmt6(linked_list list, SymTab* T, int D){sTable = T, Depth = D;LIST=list;}
    linked_list LIST;
    int Depth;
    SymTab* sTable;
    Token* FOR;
    assign* A1;
    incdecexpr* IncD;
    Stmt* S1;
    void printStmt6();
};

#endif //INC_125PROJ_STMT_H
