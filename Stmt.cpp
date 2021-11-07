//
// Created by Jared Tuck on 11/2/2021.
#include "Stmt.h"
#include "Statement.h"

Stmt1::Stmt1(linked_list* list, SymTab* T, int D) //constructor
{    //Assign => id = allexpr;
    cout<<"Stmt1 Assign found"<<endl;
    sTable = T; Depth = D; LIST=list;
    ScanCls1();
}
void Stmt1::ScanCls1(){ //Assign => id = allexpr;
    typeCheck();
    Token* temp = LIST->head;
    ID=temp->get_data();
    if(!sTable->inTable(ID)){cout<<"Undeclared ID ERROR on line "<<temp->get_LN()<<endl;}
    linked_list* AE = LIST->split_set(2, LIST->listSize()-2);
    AE->Print();
    allExpression = new allexpr(AE, sTable, Depth);
}
void Stmt1::printStmt1(){
    for(int i=0; i<=Depth; i++){cout<<"| "; }
    cout<<"+--ASSIGN"<<endl;
    for(int i=0; i<=Depth+1; i++){cout<<"| "; }
    cout<<"+--Token "<<ID<<endl;
    allExpression->printAllexpr();
}
void Stmt1::typeCheck() {
    Token *temp = LIST->head;
    string TYPE;
    bool TypeFound = false;
    while (temp) {
        if (temp->get_class() == "ID" && !sTable->inTable(temp->get_data())) {
            cout << "SCOPE ERROR on line " << temp->get_LN() << ", ID '" << temp->get_data() << "' is UN-INITILIZED."
                 << endl;
            exit(1);
        }
        if (!TypeFound && temp->get_class() == "ID") {
            TypeFound = true;
            TYPE = sTable->findType(temp->get_data());
        } else if (TypeFound && temp->get_class() == "ID") {
            if (sTable->findType(temp->get_data()) != TYPE) {
                cout << "TYPE ERROR on line " << temp->get_LN() << ", ID '" << temp->get_data()
                     << " is not compatible with type "<<TYPE<< endl;
                exit(1);
            }
        }else
        if(TypeFound){
            if(temp->get_class()=="NUM" && TYPE != "int"){
                cout << "TYPE ERROR on line " << temp->get_LN() << ", Token " << temp->get_data()
                     << " is not compatible with type "<<TYPE<< endl;
                exit(1);
            }
            if(temp->get_class()=="REAL" && TYPE != "float"){
                cout << "TYPE ERROR on line " << temp->get_LN() << ", Token " << temp->get_data()
                     << " is not compatible with type "<<TYPE<< endl;
                exit(1);
            }
            if((temp->get_class()=="false"||temp->get_class()=="true"||temp->get_class()=="bool") && TYPE != "bool"){
                cout << "TYPE ERROR on line " << temp->get_LN() << ", Token " << temp->get_data()
                     << " is not compatible with type "<<TYPE<< endl;
                exit(1);
            }
        }
        temp = temp->next;
    }
}
Stmt2::Stmt2(linked_list* list, SymTab* T, int D){
    //if (allexpr) stmt
    cout<<"Stmt2 found"<<endl;
    sTable = T, Depth = D; LIST=list;
    ScanCls2();
}

void Stmt2::ScanCls2(){
    //if(allexpr)stmt
    Token* temp=LIST->head;
    int pos=0; //index 2 starting
    int LP=0;
    int RP=0;
    int count = 0;
    linked_list* ptr;
    linked_list* ptr2;
    while(temp){
        // cout <<temp->get_data()<<endl;
        if (temp->get_data()=="(") {LP++;}
        if (temp->get_data()==")") {RP++;}
        if (LP==RP && LP!=0){ptr=LIST->split_set(2, pos-1); break;} //removing allexpr from linked list
        temp = temp->next;
        pos++;
    }

    temp = LIST->head;

    allExpression= new allexpr (ptr, sTable, Depth);
    ptr2=LIST->split_set(3, LIST->listSize()-1); //accounting for end of the list
    cout <<"this works";
    statement =new Stmt (ptr2, sTable, Depth); //stmt1
}
void Stmt2::printStmt2(){
    for(int i=0; i<=Depth; i++){cout<<"| "; }
    cout<<"+--IF"<<endl;
    allExpression->printAllexpr();
    statement->printStmt();
}

Stmt3::Stmt3(linked_list* list, SymTab* T, int D)
{   //if (allexpr) stmt else stmt
    cout<<"Stmt3 found"<<endl;
    sTable = T, Depth = D; LIST=list;
    ScanCls3();
};

void Stmt3::ScanCls3(){
    //if(allexpr) stmt else stmt
    Token* temp=LIST->head;
    int pos=0; //index 2 starting
    int LP=0;
    int RP=0;
    int count = 0;
    linked_list* ptr;
    linked_list* ptr2;
    linked_list* ptr3;
    while(temp->next){
        // cout <<temp->get_data()<<endl;
        if (temp->get_data()=="(") {LP++;}
        if (temp->get_data()==")") {RP++;}
        if (LP==RP && LP!=0){ptr=LIST->split_set(2, pos-1); break;} //removing allexpr from linked list
        temp = temp->next;
        pos++;
    }

    temp = LIST->head;
    while(temp->get_class() !="ELSE"){
        count++;
        temp = temp->next;
    }

    allExpression= new allexpr (ptr, sTable, Depth);
    ptr2=LIST->split_set(3, count-1); //accounting for end of the list
    ptr3 = LIST->split_set(4,LIST->listSize()-1);
    temp = ptr3->head;
    while(temp){
        cout<<temp->get_data();
        temp = temp->next;
    }
    S1 =new Stmt (ptr2, sTable, Depth); //stmt1
    S2 =new Stmt (ptr3,sTable, Depth); //stmt2
}
void Stmt3::printStmt3(){
    for(int i=0; i<=Depth; i++){cout<<"| "; }
    cout<<"+--IF"<<endl;
    allExpression->printAllexpr();
    S1->printStmt();
    for(int i=0; i<=Depth; i++){cout<<"| "; }
    cout<<"+--ELSE"<<endl;
    S2->printStmt();
}

Stmt4::Stmt4(linked_list* list, SymTab* T, int D)
{   //while (allexpr) stmt
    cout<<"Stmt4 found"<<endl;
    Token* temp = list->head;
    while(temp){cout<<temp->get_class()<<" ";temp=temp->next;}
    cout<<endl;
    sTable = T, Depth = D, LIST=list;
    ScanCls4();
};

void Stmt4::ScanCls4()
{   //while (allexpr) stmt
    Token* temp=LIST->head->next->next;
    int pos=2; //index 2 starting
    int LP=1;
    int RP=0;
    linked_list* ptr;
    linked_list* ptr2;
    while(temp){
        if (temp->get_data()=="(") {LP++;}
        if (temp->get_data()==")") {RP++;}
        if (LP==RP){ptr=LIST->split_set(2, pos-1); break;} //removing allexpr from linked list
        temp=temp->next;
        pos++;}
    allExpression= new allexpr (ptr, sTable, Depth);
    ptr2=LIST->split_set(3, LIST->listSize()-1); //accounting for end of the list
    statement =new Stmt(ptr2, sTable, Depth+1);
}

void Stmt4::printStmt4(){
    for(int i=0; i<=Depth; i++){cout<<"| "; }
    cout<<"+--WHILE"<<endl;
    allExpression->printAllexpr();
    statement->printStmt();
}

Stmt5::Stmt5(linked_list* list, SymTab* T, int D)
{   cout<<"Stmt5 found"<<endl;
    sTable = T, Depth = D, LIST=list;
    ScanCls5();
};

void Stmt5::ScanCls5()
{//do stmt while (allexpr) ;
    Token* temp = LIST->head;
    int count = 0;
    int stmtend = 0;
    linked_list* ptr;
    int LP =0;
    int RP = 0;
    while(temp->get_class() != "WHILE"){
        stmtend++;
        temp = temp->next;
    }
    WHILE = temp->get_class();
    S1 = new Stmt(LIST->split_set(1,stmtend-1), sTable, Depth);
    temp = LIST->head;

    while(temp){
        count++;
        if(temp->get_data() == "("){LP++;}
        if(temp->get_data() == ")"){RP++;}
        if(RP==LP && LP!=0){ptr = LIST->split_set(3,count-2);break;}
        temp = temp->next;
    }
    allExpression= new allexpr (ptr, sTable, Depth);


}

void Stmt5::printStmt5(){
    for(int i=0; i<=Depth; i++){cout<<"| "; }
    cout<<"+--DO"<<endl;
    S1->printStmt();
    for(int i=0; i<=Depth; i++){cout<<"| "; }
    cout<<"+--WHILE"<<endl;
    allExpression->printAllexpr();
}

Stmt6::Stmt6(linked_list* list, SymTab* T, int D)
{   cout<<"Stmt6 found"<<endl;
    Token* temp=list->head;
    while(temp){cout<<temp->get_data()<<" ";temp=temp->next;}
    sTable = T, Depth = D, LIST=list;
    ScanCls6();
};

void Stmt6::ScanCls6()
{   //for (assign allexpr; incdecexpr)  stmt]

    Token* temp=LIST->head;
    int pos=2; //index 2 starting
    int semipos = 1;

    FOR = LIST->head->get_class();


        if(temp->get_data() == "("){
            while(temp->get_data() != ";"){
                semipos++;
                temp = temp->next;
            }
            A1 = new Stmt1(LIST->split_set(pos,semipos), sTable, Depth++);
            break;
        }
        temp = temp->next;

    temp = temp->next;
    pos = semipos+1;//7,6
    while(temp->get_data() != ";"){
        semipos++;
        temp = temp->next;
    }
    semipos++;
    allExpression = new allexpr(LIST->split_set(pos,semipos), sTable, Depth++);

    pos = semipos+1;

    while(temp->get_data() != ")"){
        semipos++;
        temp = temp->next;
    }


    IncD = new incdecexpr(LIST->split_set(pos,semipos), sTable, Depth++);
    pos = semipos+2;
    S1 = new Stmt(LIST->split_set(pos, LIST->listSize()-1), sTable, Depth+1);
}

void Stmt6::printStmt6(){
    for(int i=0; i<=Depth; i++){cout<<"| "; }
    cout<<"+--FOR"<<endl;
    allExpression->printAllexpr();
    IncD->printIncDecEx();
    S1->printStmt();
}

Stmt::Stmt(linked_list* list, SymTab* T, int D){sTable = T; Depth = D; LIST = list; makeNewStmt();}


void Stmt::makeNewStmt() {
    cout<<"MAKE_NEW_STMT_Called"<<endl;
    cout<<Depth<<endl;
    Token *temp = LIST->head;
    bool found_flag = false;
    int lbrack = 0;
    int rbrack = 0;
    int counter = 1;
    //S2 & S3 Parsing
    if (temp->get_class() == "IF") {
        temp = temp->next;
        while (temp) {
            if (temp->get_data() == "{") {
                while (lbrack != rbrack && lbrack != 0) {
                    if (temp->get_data() == "{") { lbrack++; }
                    if (temp->get_data() == "}") { rbrack++; }
                    temp = temp->next;
                    counter++;
                }
            }

            if(counter == LIST->listSize()){break;}

            if (temp->get_class() == "ELSE"){
                S3 = new Stmt3(LIST, sTable, Depth);
                found_flag = true;
                break;
            }
            temp = temp->next;
            counter++;
        }
        //If no Else is found, S2
        if (!found_flag) { S2 = new Stmt2(LIST, sTable, Depth); }
    }else  //S4 Parsing
    if (temp->get_class() == "WHILE") { S4 = new Stmt4(LIST, sTable, Depth); }else
    //S5 Parsing
    if (temp->get_class() == "DO") { S5 = new Stmt5(LIST, sTable, Depth); }else
    //S6 Parsing
    if (temp->get_class() == "FOR") {S6 = new Stmt6(LIST, sTable, Depth); }else
    //S1 parsing
    if (temp->get_class() == "ID") { S1 = new Stmt1(LIST, sTable, Depth); }else
    if (temp->get_data() == "{") { B = new Block(Depth + 1, LIST, sTable); }else
    if(temp->get_class()=="BREAK"){BREAK="BREAK";}
    temp = LIST->head;
}
void Stmt::printStmt(){
    for(int i=0; i<Depth; i++){cout<<"| "; }
    cout<<"+--STMT"<<endl;
    if(BREAK=="BREAK"){
        for(int i=0; i<=Depth; i++){cout<<"| "; }
        cout<<"+--BREAK"<<endl;
    }else
    if(S1){S1->printStmt1();}else
    if(S2){S2->printStmt2();}else
    if(S3){S3->printStmt3();}else
    if(S4){S4->printStmt4();}else
    if(S5){S5->printStmt5();}else
    if(S6){S6->printStmt6();}else
    if(B){B->printBlock();}
}