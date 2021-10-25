#ifndef INC_125PROJ_PARSER_H
#define INC_125PROJ_PARSER_H
#include <vector>
#include "Lexer.h"
#include "Statement.h"
#include "SymTab.h"

//Block object should pass a complete statement into stmt class
//Class will determine what type of stmt it is, create a new stmt depending on type.
class Parser{
public:
    Parser(Lexer Lex);


};




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

