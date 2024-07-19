#include "graph.h"

int main(void)
{
    graph g(5);
    g.add_edge(1, 2, 1);
    g.add_edge(2, 3, 2);
    g.add_edge(1, 4, 5);
    g.add_vertex();
    g.add_edge(0, 5, 4);
    g.add_edge(4, 5, 7); // this edge makes the graph connected
    std::cout << "\nThe adjacency list of the graph : \n\n" << g << std::endl;
    std::cout << "\ng.is_connected() : " << std::boolalpha << g.is_connected() << std::endl;
    std::cout << "\n4 and 5 are adjacent : " << std::boolalpha << g.is_adjacent(4, 5) << std::endl;
    std::cout << "1 and 3 are adjacent : " << std::boolalpha << g.is_adjacent(1, 3) << std::endl;
    std::cout << "\nDegree of 2 is : " << g.deg(2) << std::endl;
    return 0;
}