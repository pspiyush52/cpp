#include "graph.h"

graph::graph(size_t vertices)
{
    size = vertices;
    alist = new list*[vertices];
    for (size_t i{}; i < size; i++)
        alist[i] = new list;
}

void graph::add_edge(size_t u, size_t v, unsigned int Weight)
{
    if (u > (size - 1) || v > (size - 1))
    {
        std::cerr << "ERROR: Vertex does not exist." << std::endl;
        return;
    }
    (*(alist[u])).insert(v, Weight);
    (*(alist[v])).insert(u, Weight);
}

void graph::add_vertex()
{
    size++;
    list** new_alist = new list* [size];
    size_t i{};
    for (; i < size - 1; i++)
        new_alist[i] = alist[i];
    new_alist[i] = new list;
    delete[] alist;
    alist = new_alist;
}

bool graph::is_connected()
{
    bool* visited = new bool[size];
    size_t i{};
    for (; i < size; i++)
        visited[i] = false;
    connected_dfs(0, visited);
    for (i = 0; i < size; i++)
        if (!visited[i])
        {
            delete[] visited;
            return false;
        }
    delete[] visited;
    return true;
}

void graph::connected_dfs(size_t v, bool* visited)
{
    visited[v] = true;
    list_node* head = (*(alist[v])).head;
    size_t cur;
    for (; head; head = head->next)
    {
        cur = head->v;
        if (!visited[cur])
            connected_dfs(cur, visited);
    }
}

bool graph::is_adjacent(size_t u, size_t v)
{
    if (u > (size - 1) || v > (size - 1))
    {
        std::cerr << "ERROR: Vertex does not exist." << std::endl;
        return false;
    }
    return (*(alist[u])).exists(v);
}

size_t graph::deg(size_t v)
{
    if (v > (size - 1))
    {
        std::cerr << "ERROR: Vertex does not exist.";
        return SIZE_MAX;
    }
    return (*(alist[v])).len();
}

std::ostream& operator<<(std::ostream& output, graph& g)
{
    size_t i{};
    for (; i < g.size - 1; i++)
        output << "{" << i << "}" << " - " << (*(g.alist[i])) << std::endl;
    output << "{" << i << "}" << " - " << (*(g.alist[i]));
    return output;
}

graph::~graph()
{
    for (size_t i{}; i < size; i++)
        delete (alist[i]);
    delete[] alist;
}