#include <iostream>
#include "graph.h"

int main(void)
{
    int u[] =    {0, 0, 0, 1, 1, 2, 2, 3, 4};
    int v[] =    {1, 2, 4, 2, 5, 3, 5, 4, 5};
    double w[] = {3, 1, 8, 2, 4, 2, 5, 7, 9};
    int n = sizeof(u) / sizeof(int);
    Graph<int> G(6);
    repeat(n)
        G.addEdge(u[i], v[i], w[i]);
    std::cout << "Graph:\n" << G << '\n';
    std::cout << "Weight = " << G.weight() << "\n\n";
    std::cout << "MST:\n" << G.KruskalMST() << '\n';
    return 0;
}
