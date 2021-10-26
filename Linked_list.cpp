//
// Created by Jared Tuck on 10/24/2021.
//
#include <string>
#include "Linked_list.h"
using namespace std;
////////////////////Linked List Functions///////////////////////////////////////
linked_list::linked_list(){
    head = tail = NULL;
}

linked_list::~linked_list(){
    Token* temp;
    while(head){
        temp = head;
        head = head->next;
        delete temp;
    }
    tail = NULL;
}

bool linked_list::isEmpty(){return (head == NULL);}

int linked_list::listSize(){
    Token* temp = head;
    if(isEmpty()){return 0;}
    int count =1;
    while(temp->next){temp = temp->next; count++; }
    return count;
}

void linked_list::push(string input, string Class){
    Token* temp = new Token(input, Class);
    if(isEmpty()){head = tail =temp;}
    else
    if(listSize()==1){
        tail->next = temp;
        tail = temp;
        tail->next = NULL;
        head->next = tail;
        tail->prev=head;
    }
    else {
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
        tail->next = NULL;
    }
}
void linked_list::pop(){
    string tok;
    if(head){tok = head->data;}
    Token* temp =head;
    head = temp->next;
    delete temp;
};
void linked_list::popEnd(){
    string tok;
    Token* temp =tail;
    tail= temp->prev;
    delete temp;
};

linked_list linked_list::split(int position){
    Token* temp = head;
    int SZ = listSize();
    int pos = 0;
    if(position >= SZ){throw 1;}
    while(pos< position){
        pos++;
        temp=temp->next;
    }
    linked_list new_list;
    if(position == 0){ new_list.head = head; new_list.tail = tail; tail = head = nullptr; }
    else {
        new_list.head = temp;
        new_list.tail = tail;
        tail = temp->prev;
        tail->next = nullptr;
        new_list.head->prev = nullptr;
    }
    return new_list;

}

linked_list* linked_list::split_set(int position_1, int position_2) {
    Token* temp1; Token* temp2; temp2 = head;
    int temp;
    if(position_1 > position_2){temp = position_1; position_1= position_2; position_2 = temp; }
    int SZ = listSize();
    int pos = 0;
    if(position_1 >= SZ || position_2 >= SZ){throw 1;}
    linked_list* new_list = new linked_list();
    while(pos < position_2){
        if(pos == position_1){temp1 = temp2;}
        temp2=temp2->next;
        pos++;
    }
    new_list->head = temp1;
    new_list->tail = temp2;

    if(temp1 == head){
        head = tail = temp2->next;
        new_list->tail->next = nullptr;
        head->prev = nullptr;
        return new_list;
    }
    if(temp2 == tail){
        tail = temp1->prev;
        new_list->head->prev = nullptr;
        tail->next = nullptr;
        return new_list;
    }
    temp1 = temp1->prev;
    new_list->head->prev = nullptr;
    temp2 = temp2->next;
    new_list->tail->next = nullptr;

    temp1->next = temp2;
    temp2->prev = temp1;

    return new_list;
}
linked_list linked_list::operator=(linked_list &rhs) {
    if(rhs.head == head){return *this;}
    Token* temp = rhs.head;
    this->~linked_list();
    while(temp){
        push(temp->get_data(), temp->get_class());
        temp = temp->next;
    }

    return *this;
}