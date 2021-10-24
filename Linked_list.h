//
// Created by Jared Tuck on 10/24/2021.
//

#ifndef INC_125PROJ_LINKED_LIST_H
#define INC_125PROJ_LINKED_LIST_H
using namespace std;
class Token {
public:
    Token *next;
    Token *prev;
    std::string data;
    std::string Class;
    Token(string data, string Class) : data(data),Class(Class), next(nullptr), prev(nullptr){};
};

class linked_list {
public:
    Token *head, *tail;
    linked_list();
    ~linked_list();
    bool isEmpty();
    int listSize();
    void push(string input, string Class);
    void pop();
    linked_list split(int pos);
    linked_list split_set(int position_1, int position_2);
};

#endif //INC_125PROJ_LINKED_LIST_H
