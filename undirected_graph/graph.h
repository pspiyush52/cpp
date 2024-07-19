#ifndef __GRAPH_H
#define __GRAPH_H

#include "adj_list.h"
#include "priority_queue.h"
#include "union_find.h"

template<typename T>
class Graph;

template<typename T>
class graphEdge{
    friend class Graph<T>;
    public:
        graphEdge(int U, int V, double Weight): u(U), v(V), weight(Weight){}
    private:
        int u{};
        int v{};
        double weight{};
};

template<typename T>
class Graph {
    public:
        Graph(int size){
            size = (size > 0) ? size : 4;
            this->A = new AdjList<T>*[size];
            repeat(size)
                this->A[i] = new AdjList<T>{};
            this->N = size;
        }
        Graph(Graph&& src){
            this->A = src.A;
            this->M = src.M;
            this->N = src.N;
            src.invalidate();
        }
        int numVertices() const{
            return this->N;
        }
        int numEdges() const{
            return this->M;
        }
        double weight(){
            double w{};
            repeat(this->N)
                for (auto& node : *(this->A[i]))
                    w += node.getWeight();
            return w;
        }
        Graph& addEdge(int u, int v, double w){
            if (out_of_range(u) || out_of_range(v))
                throw "Out of range";
            this->A[u]->append(v, w);
            this->A[v]->append(u, w);
            ++(this->M);
            return *this;
        }
        Graph KruskalMST(){
            Graph MST(this->N);
            PriorityQueue<graphEdge<T>, double> P(this->M), Q(this->M);
            DisjointSets S(this->N);
            repeat(this->N){
                for (auto& node : *(this->A[i]))
                    if (node.getVertex() > i){
                        P.insert(node.getWeight(), i, node.getVertex(), node.getWeight());
                        Q.insert(node.getWeight(), i, node.getVertex(), node.getWeight());
                    }
            }
            while (!Q.empty()){
                graphEdge<T>& x = Q.extractMin();
                std::cout << '(' << x.u << ", " << x.v << ", " << x.weight << ")  ";
            }
            std::cout << '\n';
            while (MST.numEdges() != (this->N - 1)){
                graphEdge<T>& e = P.extractMin();
                if (S.Union(e.u, e.v))
                    MST.addEdge(e.u, e.v, e.weight);
            }
            return MST;
        }
        ~Graph(){
            if (this->A){
                repeat(this->N)
                    delete this->A[i];
                delete this->A;
                this->A = {};
                this->M = this->N = {};
            }
        }
        friend std::ostream& operator<<(std::ostream& output, const Graph& G){
            repeat(G.N)
                output << '{' << i << "} -> " << *(G.A[i]) << '\n';
            return output;
        }
    private:
        AdjList<T>** A{};
        int M{};
        int N{};
        
        bool out_of_range(int v){
            return ((v < 0) || (v > this->N));
        }
        void invalidate(){
            this->A = {};
            this->M = this->N = {};
        }
};

#endif  // __GRAPH_H
