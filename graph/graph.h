#ifndef __GRAPH_H
#define __GRAPH_H

#include "list.h"

class List;

class Graph {
    public:
        Graph(unsigned int size);
        void add_edge(int u, int v, unsigned int weight);
        void add_vertex();
        bool is_connected();
        ~Graph();
    private:
        List* alist;
        size_t s;
        void __connected_dfs__(size_t, bool*);
        friend std::ostream& operator<<(std::ostream& output, Graph& g);
};

#endif // __GRAPH_H