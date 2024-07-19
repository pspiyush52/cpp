#ifndef __GUNION_H
#define __GUNION_H

#include "utils.h"

struct unionNode{
    unionNode() = default;
    unionNode(unionNode* p, int h): parent(p), height(h){}
    unionNode* parent{};
    int height{};
};

class DisjointSets {
    public:
        DisjointSets(int size){
            this->A = new unionNode*[size];
            this->n = size;
            repeat(size)
                this->A[i] = new unionNode;
        }
        bool Union(int u, int v){
            // unionNode* p_u = find(u);
            // unionNode* p_v = find(v);
            // printf("parent(%d) = %d,  ", u, p_u);
            // printf("parent(%d) = %d\n", v, p_v);
            if (find(u) == find(v))
                return false;
            if (this->A[u]->height > this->A[v]->height){
                this->A[v]->parent = this->A[u];
                ++(this->A[u]->height);
            }
            else{
                this->A[u]->parent = this->A[v];
                ++(this->A[v]->height);
            }
            return true;
        }
        unionNode* find(int v){
            unionNode* node = this->A[v];
            for (; node->parent; node = node->parent);
            return node;
        }
        ~DisjointSets(){
            repeat(this->n)
                delete this->A[i];
            delete[] this->A;
            this->A = {};
        }
    private:
        unionNode** A;
        int n;
};

#endif  // __GUNION_H