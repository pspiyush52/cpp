#ifndef __LIST_H
#define __LIST_H

#include <iostream>
#include "graph.h"

class list;

class list_node {
    public:
        list_node(size_t Vertex, unsigned int Weight);
    private:
        size_t v;
        unsigned int weight;
        list_node* next;
        friend class list;
        friend class graph;
        friend std::ostream& operator<< (std::ostream& output, list& l);
};

class list {
    public:
        list();
        void insert(size_t v, unsigned int weight);
        size_t len();
        bool exists(size_t v);
        ~list();
    private:
        list_node* head;
        size_t size;
        friend class graph;
        friend std::ostream& operator<< (std::ostream& output, list& l);
};

#endif // __LIST_H