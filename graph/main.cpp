#include "graph.h"

int main(void)
{
    Graph g(5);
    // g.add_edge(0, 4, 1); // adding this edge will make the graph connected
    g.add_edge(0, 2, 1);
    g.add_edge(0, 1, 1);
    g.add_edge(0, 3, 1);
    g.add_edge(2, 3, 1);
    std::cout << g << std::endl;
    if (g.is_connected())
        std::cout << "The graph is connected." << std::endl;
    else
        std::cout << "The graph is not connected." << std::endl;
    return 0;
}