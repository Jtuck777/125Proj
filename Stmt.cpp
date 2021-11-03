//
// Created by Jared Tuck on 11/2/2021.
#include "Stmt.h"
#include "Statement.h"

Stmt1::Stmt1(linked_list* list, SymTab* T, int D) //constructor
{
    sTable = T; Depth = D; LIST=list;
    ScanCls1();
}
void Stmt1::ScanCls1() //id terminal, equal sign, an allexpr, and a semicolon
{
    Token* temp;
    ID=temp->get_data();
    if (!sTable->inTable(ID))
    {
        cout<<"Symbol not in table"<<endl;
    }
    int equal=0;
    int semicolon=0;
    if (temp->get_data()=="=") {equal++;}
    temp=LIST->head->next->next;
    int position=2; //index 2 starting
    int LP=1;
    int RP=0;
    linked_list* ptr;
    linked_list* ptr2;
    while(temp->next)
    {
        if (temp->get_data()=="(") {RP++;}
        if (temp->get_data()==")") {RP++;}
        if (LP==RP){ptr=LIST->split_set(2, position-1); break;} //removing allexpr from linked list
    }
    allExpression= new allexpr (ptr, sTable, Depth++);
    if(temp->get_data()==";") {semicolon++;}
    ptr2=LIST->split_set(3, LIST->listSize()-1); //accounting for end of the list
}

Stmt2::Stmt2(linked_list* list, SymTab* T, int D)
{
    Public:
    sTable = T, Depth = D; LIST=list;
    ScanCls2();
}

void Stmt2::ScanCls2()
{
    Token* temp=LIST->head->next->next;
    int position=2; //index 2 starting
    int LP=1;
    int RP=0;
    linked_list* ptr;
    linked_list* ptr2;
    while(temp->next)
    {
        if (temp->get_data()=="(") {RP++;}
        if (temp->get_data()==")") {RP++;}
        if (LP==RP){ptr=LIST->split_set(2, position-1); break;} //removing allexpr from linked list
    }
    allExpression= new allexpr (ptr, sTable, Depth++);
    ptr2=LIST->split_set(3, LIST->listSize()-1); //accounting for end of the list
    statement =new Stmt (ptr2, sTable, Depth++);
}

Stmt3::Stmt3(linked_list* list, SymTab* T, int D)
{
    sTable = T, Depth = D; LIST=list;
    ScanCls3();
};

void Stmt3::ScanCls3()
{
    Token* temp=LIST->head->next->next;
    int position=2; //index 2 starting
    int LP=1;
    int RP=0;
    SymTab* sTable;
    linked_list* ptr;
    linked_list* ptr2;
    linked_list* ptr3;
    while(temp->next)
    {
        if (temp->get_data()=="(") {RP++;}
        if (temp->get_data()==")") {RP++;}
        if (LP==RP){ptr=LIST->split_set(2, position-1); break;} //removing allexpr from linked list
    }
    allExpression= new allexpr (ptr, sTable, Depth++);
    ptr2=LIST->split_set(3, LIST->listSize()-1); //accounting for end of the list
    S1 =new Stmt3 (ptr2, sTable, Depth++); //stmt1
    S2 =new Stmt3 (ptr3,sTable, Depth++); //stmt2
}

Stmt4::Stmt4(linked_list* list, SymTab* T, int D)
{
    sTable = T, Depth = D, LIST=list;
    ScanCls4();
};

void Stmt4::ScanCls4()
{
    Token* temp=LIST->head->next->next;
    int position=2; //index 2 starting
    int LP=1;
    int RP=0;
    SymTab* sTable;
    linked_list* ptr;
    linked_list* ptr2;
    while(temp->next)
    {
        if (temp->get_data()=="(") {RP++;}
        if (temp->get_data()==")") {RP++;}
        if (LP==RP){ptr=LIST->split_set(2, position-1); break;} //removing allexpr from linked list
    }
    allExpression= new allexpr (ptr, sTable, Depth++);
    ptr2=LIST->split_set(3, LIST->listSize()-1); //accounting for end of the list
    statement =new Stmt4 (ptr2, sTable, Depth++);
}

Stmt5::Stmt5(linked_list* list, SymTab* T, int D)
{
    sTable = T, Depth = D, LIST=list;
    ScanCls5();
};

void Stmt5::ScanCls5()
{
    Token* temp=LIST->head->next->next;
    int position=2; //index 2 starting
    int LP=1;
    int RP=0;
    SymTab* sTable;
    linked_list* ptr;
    int stmtend = 1;

    DO = LIST->head;
    temp = temp->next;

    while(temp->get_class() != "WHILE"){
        stmtend++;
        temp = temp->next;
    }

    WHILE = temp;

    S1 = new Stmt(LIST->split_set(2,stmtend), sTable, Depth+1);

    while(temp->next)
    {
        if (temp->get_data()=="(") {RP++;}
        if (temp->get_data()==")") {RP++;}
        if (LP==RP){ptr=LIST->split_set(2, position-1); break;} //removing allexpr from linked list
    }
    allExpression= new allexpr (ptr, sTable, Depth++);
}

Stmt6::Stmt6(linked_list* list, SymTab* T, int D)
{
    sTable = T, Depth = D, LIST=list;
    ScanCls6();
};

void Stmt6::ScanCls6()
{
    Token* temp=LIST->head->next->next;
    int position=2; //index 2 starting
    int LP=1;
    int RP=0;
    SymTab* sTable;
    linked_list* ptr;
    linked_list* ptr2;
    linked_list* ptr3;
    linked_list* ptr4;

    FOR = LIST->head;
    while(temp->next)
    {
        if (temp->get_data()=="("){
            RP++;
            ptr = LIST->split_set(2,3);//assign
            temp = temp->next;
            ptr2 = LIST->split_set(3,4);//All expr
        }
        if(temp->get_data() == ";")
            ptr3 = LIST->split_set(5,6);//Incdeepr

        if (temp->get_data()==")"){
            RP++;
        }
        if (LP==RP){ptr4=LIST->split_set(7, position-1); break;} //removing allexpr from linked list
    }
    A1 = new assign(ptr, sTable, Depth+1);
    allExpression = new allexpr(ptr2, sTable, Depth+1);
    IncD = new incdecexpr(ptr3, sTable, Depth+1);
    S1 = new Stmt(ptr4, sTable, Depth+1);
}


Stmt::Stmt(linked_list* list, SymTab* T, int D){sTable = T; Depth = D; LIST = list; }


void Stmt::makeNewStmt() {
    Token *temp = LIST->head;
    bool found_flag = false;
    int lbrack = 0;
    int rbrack = 0;
    //S2 & S3 Parsing
    if (temp->get_class() == "IF") {
        temp = temp->next;
        while (temp) {
            if (temp->get_data() == "{") {
                lbrack++;
                while (lbrack != rbrack && lbrack != 0) {
                    if (temp->get_data() == "{"){lbrack++;}
                    if (temp->get_data() == "}"){rbrack++;}
                    temp = temp->next;
                }
                temp = temp->next;
                if (temp->get_class() == "ELSE") {
                    S3 = new Stmt3(LIST, sTable, Depth + 1);
                    found_flag = true;
                    break;
                }}}
        //If no Else is found, S2
        if (!found_flag) { S2 = new Stmt2(LIST, sTable, Depth + 1); }
        //S4 Parsing
        if (temp->get_class() == "WHILE") { S4 = new Stmt4(LIST, sTable, Depth + 1); }
        //S5 Parsing
        if (temp->get_class() == "DO") { S5 = new Stmt5(LIST, sTable, Depth + 1); }
        //S6 Parsing
        if (temp->get_class() == "FOR") { S6 = new Stmt6(LIST, sTable, Depth + 1); }
        //S1 parsing
        if (temp->get_class() == "ID") { S1 = new Stmt1(LIST, sTable, Depth + 1); }
        if (temp->get_data() == "{") { B = new Block(Depth + 1, LIST->split_set(0, LIST->listSize()-1), sTable); }
        temp = LIST->head;
    }
}