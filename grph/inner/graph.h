#ifndef __GRAPH_H
#define __GRAPH_H

#include "list.h"
class list;
class graph {
    public:
        graph(size_t vertices);
        void add_edge(size_t u, size_t v, unsigned int Weight);
        void add_vertex();
        bool is_connected();
        bool is_adjacent(size_t u, size_t v);
        size_t deg(size_t v);
        ~graph();
    private:
        list** alist;
        size_t size;
        void connected_dfs(size_t v, bool*);
        friend std::ostream& operator<<(std::ostream& output, graph& g);
};

#endif // __GRAPH_H