//
// Created by Jared Tuck on 10/24/2021.
//

#ifndef INC_125PROJ_MISCCLASS_H
#define INC_125PROJ_MISCCLASS_H
#include "linked_list.h"
#include "SymTab.h"


class allexpr   {public: allexpr(linked_list list, SymTab* T, int Depth);};

class incdecexpr{
    // id++ | id--
public:
    incdecexpr(linked_list list, SymTab* T, int D){sTable = T, Depth = D;}
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
    factor(linked_list list, SymTab* T, int D){sTable = T, Depth = D;}
    int Depth;
    SymTab* sTable;
    allexpr* allExpression;
    incdecexpr* IncDec;
    Token* tok;
    void printFactor();
};
class term      {
    //term * factor | term / factor | factor
public: term(linked_list list, SymTab* T, int D){sTable = T, Depth = D;}
    int Depth;
    SymTab* sTable;
    term* T1;
    Token* Sym;
    factor* F1;
    void printTerm();
};
class expr      {public: expr(linked_list list, SymTab* T, int D);};
class rel       {public: rel(linked_list list, SymTab* T, int D); };
class equal     {public: equal(linked_list list, SymTab* T, int D);};
class andexpr   {public: andexpr(linked_list list, SymTab* T, int D);};
class assign    {
    //id = allepr
public:
    assign(linked_list list, SymTab* T, int D){sTable = T, Depth = D;}
    int Depth;
    SymTab* sTable;
    allexpr* allExpression;
    Token* ID;
    void printAssign();
};

#endif //INC_125PROJ_MISCCLASS_H
