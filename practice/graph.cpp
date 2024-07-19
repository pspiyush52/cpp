#include "list.h"
#include "lists.h"
#include "queue.h"

template<typename T>
class Graph{
    public:
        typedef                                  T             value_type;
        typedef                                  T*            pointer;
        typedef                            const T*            const_pointer;
        typedef                                  T&            reference;
        typedef                            const T&            const_reference;
        typedef         arr::List<List<value_type>>            AdjList;
    public:
        Graph() : __alist(new AdjList()){}
        Graph(int size){
            this->__alist = new AdjList();
            for (int i{}; i < size; ++i)
                this->__alist->append({});
        }
        size_t size() const{
            return this->__alist->size();
        }
        Graph& add_vertex(){
            this->__alist->append({});
            return *this;
        }
        Graph& add_edge(int from, int to){
            (this->__alist->operator[](from)).append(to);
            // (this->__alist->operator[](to)).append(from);
            return *this;
        }
        friend std::ostream& operator<<(std::ostream& output, const Graph& g){
            if (g.__alist->is_empty()){
                output << "{ }";
            }
            else{
                AdjList& alist = *(g.__alist);
                for (size_t i{}, size = g.size(); i < size; ++i)
                    output << "{ " << i << " } --> " << alist[i] << '\n';
            }
            return output;
        }
        void dfs(){
            this->__dfs__(0);
        }
        int distance(int from, int to){
            return this->__distance__(from, to);
        }
        ~Graph(){
            delete this->__alist;
            this->__alist = {};
        }
    private:
        AdjList* __alist{};
        void __dfs_main__(int v, bool* visited, int level){
            visited[v] = true;
            std::cout << v <<  ", level: " << level << '\n';
            auto& l = this->__alist->operator[](v);
            for (auto& w : l)
                if (!visited[w])
                    __dfs_main__(w, visited, level + 1);
        }
        void __dfs__(int v){
            bool* visited = new bool[this->size()]{};
            __dfs_main__(v, visited, 0);
            delete[] visited;
        }
        void __bfs_main__(int v, int* distances){
            bool* visited = new bool[this->size()]{};
            Queue<int> q;
            visited[v] = true;
            q.enqueue(v);
            while (!q.is_empty()){
                int w = q.front();
                auto& l = this->__alist->operator[](w);
                for (auto& n : l)
                    if (!visited[n]){
                        visited[n] = true;
                        distances[n] = distances[w] + 1;
                        q.enqueue(n);
                    }
                q.dequeue();
            }
            delete[] visited;
        }
        void __bfs__(int v){
            int* distances = new int[this->size()]{};
            this->__bfs_main__(v, distances);
            delete[] distances;
        }
        int __distance__(int from, int to){
            int* distances = new int[this->size()]{};
            this->__bfs_main__(from, distances);
            int dist = distances[to];
            delete[] distances;
            return dist;
        }
};

int main(void)
{
    Graph<int> g(5);
    g.add_edge(0, 2);
    g.add_edge(0, 3);
    g.add_edge(0, 4);
    g.add_edge(2, 1);
    g.add_edge(3, 4);
    std::cout << g;
    std::cout << g.distance(0, 1);
    return 0;
}