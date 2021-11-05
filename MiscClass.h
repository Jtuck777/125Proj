//
// Created by Jared Tuck on 10/24/2021.
//
#ifndef INC_125PROJ_MISCCLASS_H
#define INC_125PROJ_MISCCLASS_H
#include "linked_list.h"
#include "SymTab.h"
class andexpr;

class allexpr   {
    //allexpr || andexpr | andexpr
public:
    allexpr(linked_list* list, SymTab* T, int D);
    linked_list* LIST;
    int Depth;
    SymTab* sTable;
    allexpr* AE1;
    andexpr* AE2;
    void allexpScan();  //scans linkedlist to find allexp seg
};


class incdecexpr{
    // id++ | id--
public:
    incdecexpr(linked_list* list, SymTab* T, int D);
    linked_list* LIST;
    int Depth;
    SymTab* sTable;
    string ID;
    string s1, s2;
};


class factor{
public:
    //(allexpr) | incdecexpr | id | num | real | true | false
    factor(linked_list* list, SymTab* T, int D);
    linked_list* LIST;
    int Depth;
    SymTab* sTable;
    allexpr* allExpression;
    incdecexpr* IncDec;
    string tok;
    void scan();
};

class term{
    //term * factor | term / factor | factor
public:
    term(linked_list* list, SymTab* T, int D);
    linked_list* LIST;
    int Depth;
    SymTab* sTable;
    term* T1;
    Token* Sym;
    factor* F1;
    void termScan();
};

class expr      {
    // expr + term | expr - term | term
public:
    expr(linked_list* list, SymTab* T, int D);
    linked_list* LIST;
    int Depth;
    SymTab* sTable;
    expr* E1;
    Token* Sym;
    term* T1;
    void exprScan();
};



class rel       {
    //expr<expr | expr<=expr | expr>expr | expr>=expr | expr
public:
    rel(linked_list* list, SymTab* T, int D);
    linked_list* LIST;
    int Depth;
    SymTab* sTable;
    expr* E1;
    string Sym;
    expr* E2;
    void PrintRel(linked_list* list, SymTab* T, int D);
    void relScan();
};

class EQ     {
    // equal==rel | equal != rel | rel
public:
    EQ(linked_list* list, SymTab* T, int D);
    linked_list* LIST;
    int Depth;
    SymTab* sTable;
    EQ* E1;
    Token* Sym;
    rel* R1;
    void PrintEqual(linked_list* list, SymTab* T, int D);
    void EqScan();
};

class andexpr   {
    // andexpr && equal | equal
public:
    andexpr(linked_list* list, SymTab* T, int D);
    linked_list* LIST;
    int Depth;
    SymTab* sTable;
    andexpr* AE1;
    Token* AND;
    EQ* E1;
    void PrintAndExpr(linked_list* list, SymTab* T, int D);
    void andScan();
};

class assign{
    //id = allepr
public:
    assign(linked_list* list, SymTab* T, int D);
    linked_list* LIST;
    int Depth;
    SymTab* sTable;
    allexpr* allExpression;
    string ID;
    void printAssign(linked_list* list, SymTab* T, int D);
    void assignScan();
};



#endif //INC_125PROJ_MISCCLASS_H
