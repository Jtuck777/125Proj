//
// Created by Jared Tuck on 10/24/2021.
//
#include <string>
#include <iostream>
#include "MiscClass.h"
using namespace std;

//allexpr Functions
allexpr::allexpr(linked_list* list, SymTab* T, int D)
{   cout<<" ALLEXPR_CALLED "<<endl;
    sTable = T, Depth = D; LIST = list;
    allexpScan();
}
void allexpr::allexpScan()
//allexpr || andexpr | andexpr
{   cout<<"ALLEXPR Listsize()="<<LIST->listSize()<<endl;
    Token *temp = LIST -> head;
    bool inside = false;
    int rp = 0, lp = 0, rb = 0, lb = 0, pos = 0;
    if(LIST->listSize()==1){AE2 = new andexpr(LIST, sTable, Depth + 1);}else {
        while (temp) {
            if (temp->get_data() == "(") rp++;
            if (temp->get_data() == ")") lp++;
            if (temp->get_data() == "{") rb++;
            if (temp->get_data() == "}") lb++;

            if ((rp != lp) || (rb != lb)) inside = true;
            else inside = false;

            if (!inside && temp->get_class() == "OR") {
                linked_list *temp3 = LIST->split_set(0, pos - 1);
                linked_list *temp4 = LIST->split_set(1, LIST->listSize() - 1);
                AE1 = new allexpr(temp3, sTable, Depth + 1);
                AE2 = new andexpr(temp4, sTable, Depth + 1);
                break;
            }
            pos++;
            temp = temp->next;
            if (!temp){ AE2 = new andexpr(LIST, sTable, Depth + 1);}
        }

    }
}

incdecexpr::incdecexpr(linked_list* list, SymTab* T, int D)
{   cout<<" INCDEC_EXPRES_CALLED "<<endl;
    sTable = T, Depth = D;LIST = list;
    Token* temp = LIST -> head;
    ID = temp ->get_data();
    temp = temp -> next;
    s1 = temp->get_data();
    s2 = temp ->next ->get_data();

}
//factor functions
factor::factor(linked_list* list, SymTab* T, int D)
{   cout<<" FACTOR CALLED "<<endl;
    sTable = T, Depth = D;LIST = list;
    scan();
}
void factor::scan()
//(allexpr) | incdecexpr | id | num | real | true | false
{
    Token* temp = LIST -> head;
    if(temp -> get_data() == "(")
    {
        linked_list* temp2 = LIST -> split_set(1, LIST->listSize()-2);
        allExpression = new allexpr(temp2, sTable, Depth + 1);
    }
    else if(LIST ->listSize() > 1)
    {
        IncDec = new incdecexpr(LIST, sTable, Depth + 1);
    }
    else
    {
        tok = temp->get_class();
        cout<<"Found Terminal "<<tok<<endl;
    }
}

//Term Function
term::term(linked_list* list, SymTab* T, int D)
{   cout<<" TERM_CALLED "<<endl;
    sTable = T, Depth = D; LIST = list;
    termScan();

}
void term::termScan()
//term * factor | term / factor | factor
{
    Token* temp = LIST -> head;
    bool inside;
    int rp = 0, lp = 0, rb = 0, lb = 0, pos = 0;
    while(temp)
    {
        if (temp -> get_data() == "(")   rp++;
        if (temp ->get_data() == ")")   lp++;
        if (temp ->get_data() == "{")   rb++;
        if (temp ->get_data() == "}")   lb++;

        if( (rp != lp) || (rb != lb))   inside = true;
        else inside = false;
        string tok = temp ->get_class();
        bool symfound = false;
        if(tok == "*") symfound = true;
        if(tok == "/") symfound = true;

        if(!inside && symfound)
        {
            linked_list* temp3 = LIST -> split_set(0, pos - 1);
            linked_list* temp4 = LIST -> split_set(1, LIST->listSize() - 1);
            T1 = new term(temp3, sTable, Depth + 1);
            F1 = new factor(temp4, sTable, Depth + 1);
            break;
        }
        pos++;temp=temp->next;
        if(!temp){F1 = new factor(LIST, sTable, Depth + 1);}
    }

}

//Expr Function
expr::expr(linked_list* list, SymTab* T, int D)
{   cout<<" EXPR_CALLED "<<endl;
    sTable = T, Depth = D;LIST = list;
    exprScan();}

void expr::exprScan()
// expr + term | expr - term | term
{
    Token *temp = LIST -> head;
    bool inside;
    int rp = 0, lp = 0, rb = 0, lb = 0, pos = 0;
    while(temp)
    {
        if (temp -> get_data() == "(")   rp++;
        if (temp ->get_data() == ")")   lp++;
        if (temp ->get_data() == "{")   rb++;
        if (temp ->get_data() == "}")   lb++;

        if( (rp != lp) || (rb != lb))   inside = true;
        else inside = false;
        string tok = temp ->get_class();
        bool symfound = false;
        if(tok == "+") symfound = true;
        if(tok == "-") symfound = true;


        if(!inside && symfound)
        {
            linked_list* temp3 = LIST -> split_set(0, pos - 1);
            linked_list* temp4 = LIST -> split_set(1, LIST->listSize() - 1);
            E1 = new expr(temp3, sTable, Depth + 1);
            T1 = new term(temp4, sTable, Depth + 1);
            break;
        }
        pos++;temp=temp->next;
        if(!temp){T1 = new term(LIST, sTable, Depth + 1);}
    }
}

//rel Function
rel::rel(linked_list* list, SymTab* T, int D)
{   cout<<" REL_CALLED "<<endl;
    sTable = T, Depth = D; LIST = list;
    relScan();
}
void rel::relScan()
//expr<expr | expr<=expr | expr>expr | expr>=expr | expr
{
    Token *temp = LIST -> head;
    bool inside;
    int rp = 0, lp = 0, rb = 0, lb = 0, pos = 0;
    while(temp)
    {
        if (temp -> get_data() == "(")   rp++;
        if (temp ->get_data() == ")")   lp++;
        if (temp ->get_data() == "{")   rb++;
        if (temp ->get_data() == "}")   lb++;

        if( (rp != lp) || (rb != lb))   inside = true;
        else inside = false;
        string tok = temp ->get_data();
        bool symfound = false;
        if(tok == "<") symfound = true;
        if(tok == ">") symfound = true;
        if(tok == "<=") symfound = true;
        if(tok == ">=") symfound = true;

        if(!inside && symfound)
        {
            linked_list* temp3 = LIST -> split_set(0, pos - 1);
            linked_list* temp4 = LIST -> split_set(1, LIST->listSize() - 1);
            E1 = new expr(temp3, sTable, Depth + 1);
            T1 = new expr(temp4, sTable, Depth + 1);
            break;
        }
        pos++;
        temp=temp->next;
        if(!temp){ T1 = new expr(LIST, sTable, Depth + 1);}
    }


}
EQ::EQ(linked_list* list, SymTab* T, int D)
{   cout<<" EQ_CALLED "<<endl;
    sTable = T, Depth = D; LIST = list;
    EqScan();
}
void EQ::EqScan()
// equal==rel | equal != rel | rel
{
    Token *temp = LIST -> head;
    bool inside;
    int rp = 0, lp = 0, rb = 0, lb = 0, pos = 0;
    while(temp)
    {
        if (temp ->get_data() == "(")   rp++;
        if (temp ->get_data() == ")")   lp++;
        if (temp ->get_data() == "{")   rb++;
        if (temp ->get_data() == "}")   lb++;

        if( (rp != lp) || (rb != lb))   inside = true;
        else inside = false;
        string tok = temp ->get_class();
        bool symfound = false;
        if(tok == "EQ") symfound = true;
        if(tok == "NE") symfound = true;

        if(!inside && symfound)
        {
            linked_list* temp3 = LIST -> split_set(0, pos - 1);
            linked_list* temp4 = LIST -> split_set(1, LIST->listSize() - 1);
            E1 = new EQ(temp3, sTable, Depth + 1);
            R1 = new rel(temp4, sTable, Depth + 1);
            break;
        }
        pos++;
        temp=temp->next;
        if(!temp){ R1 = new rel(LIST, sTable, Depth + 1);}
    }


}
andexpr::andexpr(linked_list* list, SymTab* T, int D)
{   cout<<" ANDEXPR_CALLED "<<endl;
    sTable = T, Depth = D;LIST = list;
    andScan();
}

void andexpr::andScan()
// andexpr && equal | equal
{
    Token *temp = LIST -> head;
    bool inside;
    int rp = 0, lp = 0, rb = 0, lb = 0, pos = 0;
    while(temp)
    {
        if (temp -> get_data() == "(")   rp++;
        if (temp ->get_data() == ")")   lp++;
        if (temp ->get_data() == "{")   rb++;
        if (temp ->get_data() == "}")   lb++;

        if( (rp != lp) || (rb != lb))   inside = true;
        else inside = false;
        string tok = temp ->get_class();

        if(!inside && tok == "AND")
        {
            linked_list* temp3 = LIST -> split_set(0, pos - 1);
            linked_list* temp4 = LIST -> split_set(1, LIST->listSize() - 1);
            AE1 = new andexpr(temp3, sTable, Depth + 1);
            E1 = new EQ(temp4, sTable, Depth + 1);
            break;
        }
        temp=temp->next;
        pos++;
        if(!temp){ E1 = new EQ(LIST, sTable, Depth + 1);}
    }
}
assign::assign(linked_list* list, SymTab* T, int D)
{   cout<<" ASSIGN_CALLED "<<endl;
    sTable = T, Depth = D;LIST = list;
}
void assign::assignScan()
//id = allepr
{
    Token* temp = LIST -> head;
    ID = temp -> get_data();
    linked_list* temp2 = LIST -> split_set(2, LIST -> listSize() - 1);
    if(temp -> get_class() == "=") allExpression = new allexpr(temp2, sTable, Depth + 1);
}
