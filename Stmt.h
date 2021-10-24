//
// Created by Jared Tuck on 10/24/2021.
//

#ifndef INC_125PROJ_STMT_H
#define INC_125PROJ_STMT_H
#include "Parser.h"

class Stmt1{
    //Assign
    Stmt1(linked_list list, SymTab* T, int D){ sTable = T; Depth = D;}
    int Depth;
    SymTab* sTable;
    string ID;
    allexpr* allExpression;
    void printStmt1(); //Prints "|" according to depth, and the corresponding components. ID, allexpr.
};
////////////////////////////////////////////////////////////////////
class Stmt2{
    //if(allexpr)stmt
    Stmt2(linked_list list, SymTab* T, int D){sTable = T, Depth = D;}
    int Depth;
    SymTab* sTable;
    string IF = "IF";
    allexpr* allExpression;
    Stmt* statement;
    void printStmt2();
};
///////////////////////////////////////////////////////////////////
class Stmt3{
    //if(allexpr) stmt else stmt
    Stmt3(linked_list list, SymTab* T, int D){sTable = T, Depth = D;}
    int Depth;
    SymTab* sTable;
    allexpr* allExpresion;
    string IF = "IF";
    Stmt* S1;
    string ELSE = "ELSE";
    Stmt* S2;
    void printStmt3();
};
////////////////////////////////////////////////////////////////////
class Stmt4{
    //while(allexpr)stmt
    Stmt4(linked_list list, SymTab* T, int D){sTable = T, Depth = D;}
    int Depth;
    SymTab* sTable;
};
////////////////////////////////////////////////////////////////////
class Stmt5{
    //do stmt while(allexpression);

};
#endif //INC_125PROJ_STMT_H
