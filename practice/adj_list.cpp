#include "print.h"
#include "frand.h"
#include "deque_t.h"

class graph{
    public:
        graph(int n){
            repeat(n) adj.push_back({});
        }
        graph& edge(int u, int v){
            this->adj[u].push_back(v);
            this->adj[v].push_back(u);
            return *this;
        }
        graph& add_vertex(){
            this->adj.push_back({});
            return *this;
        }
        void dfs(int v){
            deque<bool> visited;
            repeats(this->adj.size()) visited.push_back({});
            this->__dfs__(visited, v);
        }
        friend std::ostream& operator<<(std::ostream& output, const graph& g){
            repeats(g.adj.size())
                output << '[' << i << "] --> " << g.adj[i] << '\n';
            return output;
        }
    private:
        deque<deque<int>> adj{};
        
        void __dfs__(deque<bool>& visited, int v){
            visited[v] = true;
            std::cout << v << "  ";
            for (auto& u : this->adj[v])
                if (!visited[u])
                    __dfs__(visited, u);
        }
};

int main(void)
{
    graph g(5);
    g.edge(0, 1).edge(0, 2).edge(0, 3).edge(1, 2).edge(1, 3).edge(4, 3).add_vertex().edge(2, 5).edge(5, 1);
    print(g);
    g.dfs(2);
    return 0;
}
