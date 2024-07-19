#ifndef __LIST_H
#define __LIST_H

#include <iostream>
#include "graph.h"

#define repeat(N) for(int i = 0; i < N; i++)
#define repeati(N, i) for(i = 0; i < N; i++)

class List;

class list_node {
    public:
        friend class List;
        friend class Graph;
        friend class edge_list;
    private:
        list_node(size_t num, unsigned int weight);
        size_t v;
        unsigned int weight;
        list_node* next;
        friend std::ostream& operator<<(std::ostream& output, List& l);
};

class List {
    public:
        List();
        void insert(size_t v, unsigned int weight);
        size_t len();
        void remove(size_t v);
        size_t pop();
        ~List();
        friend class edge_list;
        friend class Graph;
    private:
        list_node* head;
        size_t size;
        friend std::ostream& operator<<(std::ostream& output, List& l);
};

#endif // __LIST_H