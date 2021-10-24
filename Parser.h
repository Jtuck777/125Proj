#ifndef INC_125PROJ_PARSER_H
#define INC_125PROJ_PARSER_H
#include <vector>
#include "Lexer.h"
#include "Stmt.h"


class Decl{
    friend class SymTab;
public:
    Decl(std::string T, std::string I){type = T; id = I;}
    std::string type;
    std::string id;
};

/////////////////////////////////////////////////////////

class SymTab{
public:
    SymTab();
    SymTab(SymTab* T){prev = T;};
    SymTab* prev;
    std::vector<Decl> D;
    void push(Decl d){ D.push_back(d);};

    bool inTable(std::string I){ int i=0; while(i<D.size()){if(D[i].id == I){return true; }}}
    std::string findType(std::string I){ int i=0; while(i<D.size()){if(D[i].id == I){return D[i].type; }}}
};
//////////////////////////////////////////////////////////////////////
class incdecexpr{public: incdecexpr(linked_list list, SymTab* T, int Depth);};
class factor    {public: factor(linked_list list, SymTab* T, int Depth);};
class term      {public: term(linked_list list, SymTab* T, int Depth);};
class expr      {public: expr(linked_list list, SymTab* T, int Depth);};
class rel       {public: rel(linked_list list, SymTab* T, int Depth); };
class equal     {public: equal(linked_list list, SymTab* T, int Depth);};
class andexpr   {public: andexpr(linked_list list, SymTab* T, int Depth);};
class allexpr   {public: allexpr(linked_list list, SymTab* T, int Depth);};

////////////////////////////////////////////////////////////////////////
class Stmt{
public:
    Stmt(linked_list list, SymTab* T, int D){sTable = T; Depth = D;};
    SymTab* sTable;
    int Depth;
    Stmt1* S1;
    Stmt2* S2;
    Stmt3* S3;
};

////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////

class Block{
    friend class Prog;
    friend class linked_list;
public:
    Block(int D){Depth = D;};
    Block(SymTab* T);
    std::vector<Stmt> St;
    SymTab Table;
    int Depth;
    void Scan4Stmt(linked_list List){
        //Scan for end of stmt or check for declaration
        //Add newly created Decl to sym Table
        // or Add newly created stmt to stmt Vector
    };


};

class Prog{
public:
    Block* B;
    Prog(Block* b){B=b;}
    int Depth = 0;

};

#endif //INC_125PROJ_PARSER_H

