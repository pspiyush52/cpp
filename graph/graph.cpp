#include "graph.h"

Graph::Graph(unsigned int size)
{
    alist = new List[size];
    s = size;
}

void Graph::add_edge(int u, int v, unsigned int weight)
{
    if ((u < 0) || (v < 0) || (u > s - 1) || (v > s - 1))
    {
        std::cerr << "ERROR: Invalid vertex value." << std::endl;
        return;
    }
    (alist[u]).insert(v, weight);
    (alist[v]).insert(u, weight);
}

void Graph::add_vertex()
{
    List* new_alist = new List[s + 1];
    size_t i;
    repeati(s, i)
        new_alist[i] = alist[i];
    delete[] alist;
    alist = new_alist;
    s++;
}

bool Graph::is_connected()
{
    size_t i;
    bool* visited = new bool[s];
    bool flag = true;
    __connected_dfs__(0, visited);
    repeati(s, i)
        if (!(visited[i]))
        {
            flag = false;
            break;
        }
    
    delete[] visited;
    return flag;
}

void Graph::__connected_dfs__(size_t v, bool* visited)
{
    visited[v] = true;
    list_node* head = alist[v].head;
    for (; head; head = head->next)
        if (!(visited[head->v]))
            __connected_dfs__(head->v, visited);
}

Graph::~Graph()
{
    repeat(s)
        (alist[i]).~List();
    delete[] alist;
    s = 0;
}

std::ostream& operator<<(std::ostream& output, Graph& g)
{
    if (!g.alist)
        output << "{}";
    else
    {
        size_t i;
        repeati(g.s - 1, i)
            output << "{" << i  << "} - " << g.alist[i] << std::endl;
        output << "{" << i  << "} - " << g.alist[i];
    }
    return output;
}