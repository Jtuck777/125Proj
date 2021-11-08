//
// Created by Jared Tuck on 11/5/2021.
//
#include "SymTab.h"


SymTab::SymTab(){ S = new linked_list(); prev= nullptr;}
SymTab::SymTab(SymTab* T){S= new linked_list(); prev = T;}

void SymTab::push(string ID, string Type){S->push(ID, Type, 0); SZ++;}

bool SymTab::inTable(std::string I){
    Token* temp = S->head;
    bool valid = false;
    while(temp){
        if(temp->get_data()==I){valid=true; break;}
        temp=temp->next;
    }
     if(!valid && prev){return prev->inTable(I);}
     else{return valid;}

}
string SymTab::findType(string I) {
    Token *temp = S->head;

    while (temp) {
        if (temp->get_data() == I) { return temp->get_class(); }
        temp=temp->next;
    }
    if(prev){return prev->findType(I);}
    cout<<"No type found for token "<<I; exit(1);

}