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
public: allexpr(linked_list list, SymTab* T, int D){sTable = T, Depth = D;LIST = list;}
    linked_list LIST;
    int Depth;
    SymTab* sTable;
    allexpr* AE1;
    andexpr* AE2;
    void printAllEx();
};

class incdecexpr{
    // id++ | id--
public:
    incdecexpr(linked_list list, SymTab* T, int D){sTable = T, Depth = D;LIST = list;}
    linked_list LIST;
    int Depth;
    SymTab* sTable;
    Token* ID;
    Token* plus;
    Token* sub;
    void printIncDecEx();
};
class factor{
public:
    //(allexpr) | incdecexpr | id | num | real | true | false
    factor(linked_list list, SymTab* T, int D){sTable = T, Depth = D;LIST = list;}
    linked_list LIST;
    int Depth;
    SymTab* sTable;
    allexpr* allExpression;
    incdecexpr* IncDec;
    Token* tok;
    void printFactor();
};
class term      {
    //term * factor | term / factor | factor
public:
    term(linked_list list, SymTab* T, int D){sTable = T, Depth = D; LIST = list;}
    linked_list LIST;
    int Depth;
    SymTab* sTable;
    term* T1;
    Token* Sym;
    factor* F1;
    void printTerm();
};
class expr      {
    // expr + term | expr - term | term
public:
    expr(linked_list list, SymTab* T, int D){sTable = T, Depth = D;LIST = list;}
    linked_list LIST;
    int Depth;
    SymTab* sTable;
    expr* E1;
    Token* Sym;
    term* T1;
    void PrintExpr();
};
class rel       {
    //expr<expr | expr<=expr | expr>expr | expr>=expr | expr
public:
    rel(linked_list list, SymTab* T, int D){sTable = T, Depth = D;LIST = list;}
    linked_list LIST;
    int Depth;
    SymTab* sTable;
    expr* E1;
    Token* Sym;
    expr* T1;
    void PrintRel(); };

class EQ     {
    // equal==rel | equal != rel | rel
public:
    EQ(linked_list list, SymTab* T, int D){sTable = T, Depth = D;LIST = list;}
    linked_list LIST;
    int Depth;
    SymTab* sTable;
    EQ* E1;
    Token* Sym;
    rel* R1;
    void PrintEqual();
};

class andexpr   {
    // andexpr && equal | equal
public:
    andexpr(linked_list list, SymTab* T, int D){sTable = T, Depth = D;LIST = list;}
    linked_list LIST;
    int Depth;
    SymTab* sTable;
    andexpr* AE1;
    Token* AND;
     EQ* E1;
    void PrintAndExpr();};
class assign    {
    //id = allepr
public:
    assign(linked_list list, SymTab* T, int D){sTable = T, Depth = D;LIST = list;}
    linked_list LIST;
    int Depth;
    SymTab* sTable;
    allexpr* allExpression;
    Token* ID;
    void printAssign();
};

#endif //INC_125PROJ_MISCCLASS_H
