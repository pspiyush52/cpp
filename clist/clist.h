#ifndef __CLIST_H
#define __CLIST_H

#include <iostream>
#include "utils.h"

class node {
    public:
        int num;
        node* next;
};

class List {
    public:
        List();
        void append(int);
        size_t find(int);
        void display();
        size_t len();
        node* __get_tail__();
        int& operator[](long long);
        int pop();
        ~List();
    
    private:
        node* tail;
        node* create(int num)
        {
            node* ptr = new node;
            ptr->next = nullptr;
            ptr->num = num;
            return ptr;
        }
        size_t size;
        errno_t err;
};

std::ostream& operator<<(std::ostream& output, List& l);
int error(size_t);

#endif // __CLIST_H