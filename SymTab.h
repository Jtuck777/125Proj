//
// Created by Jared Tuck on 10/24/2021.
//

#ifndef INC_125PROJ_SYMTAB_H
#define INC_125PROJ_SYMTAB_H
#include <vector>
#include "Decl.h"
using namespace std;

class SymTab{
public:
    SymTab(){ prev= nullptr;}
    SymTab(SymTab* T){prev = T;}
    SymTab* prev;
    std::vector<Decl*> D;
    void push(Decl* d){ D.push_back(d);};

    bool inTable(std::string I){ return true;};
    std::string findType(std::string I){ return "string";};
};

#endif //INC_125PROJ_SYMTAB_H
