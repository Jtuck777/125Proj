//
// Created by Jared Tuck on 11/5/2021.
//
#include "SymTab.h"
#include "linked_list.h"



SymTab::SymTab(){ S = new linked_list; prev= nullptr;}
SymTab::SymTab(SymTab* T){S= new linked_list; prev = T;}

void SymTab::push(string ID, string Type){S->push(ID, Type, 0);}

bool SymTab::inTable(std::string I){//return true;
    S->head = nullptr;
    Token* temp = S->head;
    bool valid = false;
    while(temp){
        if(temp->get_data()==I){cout<<"VERIFIED "<<I<<endl;valid=true;}
        temp=temp->next;
    }
    // if(!valid && prev){return prev->inTable(I);}
    // else{return valid;}
    return valid;
}
std::string findType(std::string I){ return "string";};