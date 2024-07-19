#ifndef __HEAP_H
#define __HEAP_H

#include <iostream>
#include <stdlib.h>
#include "functors.h"

template<typename T, typename Comparator = less, typename Projection = identity>
class Heap{
    static const int DEFAULT_SIZE{4};
    public:
        typedef             T       value_type;
        typedef             T*      pointer;
        typedef       const T*      const_pointer;
        typedef             T&      reference;
        typedef       const T&      const_reference;
    
    public:
        Heap(): Heap(DEFAULT_SIZE){}
        Heap(int size){
            this->make(size);
            comp = Comparator();
            proj = Projection();
        }
        Heap(Comparator c, Projection p): comp(c), proj(p){
            this->make(DEFAULT_SIZE);
        }
        bool isEmpty() const{
            return (!this->n);
        }
        Heap& insert(const_reference item){
            if (this->isFull())
                this->expandArray();
            int p = this->parent(this->n), i = this->n;
            this->A[i] = item;
            while ((p >= 0) && comp(proj(this->A[i]), proj(this->A[p]))){
                arraySwap(i, p);
                i = p;
                p = this->parent(i);
            }
            ++(this->n);
            return *this;
        }
        value_type extract(){
            value_type retVal{this->A[0]};
            --(this->n);
            this->arraySwap(0, this->n);
            this->heapify(0);
            return retVal;
        }
        ~Heap(){
            free(this->A);
            this->A = {};
            this->n = {};
            this->size = {};
        }
        template<typename U, typename C, typename P>
        friend std::ostream& operator<<(std::ostream& output, const Heap<U, C, P>& H){
            output.put('[');
            if (!H.isEmpty()){
                int i{};
                for (; i < (H.n - 1); ++i)
                    output << H.A[i].x << ", ";
                output << H.A[i].x;
            }
            output.put(']');
            return output;
        }
        
    private:
        T* A{};
        int n{};
        int size{DEFAULT_SIZE};
        Comparator comp;
        Projection proj;
        inline static int l{}, r{}, smallest{};

        void make(int size = DEFAULT_SIZE){
            size = (size < DEFAULT_SIZE) ? DEFAULT_SIZE : size;
            this->A = (value_type*) malloc(size * sizeof(value_type));
            this->size = size;
        }
        bool isFull(){
            return (this->n == this->size);
        }
        void arraySwap(int i, int j){
            value_type tmp = this->A[i];
            this->A[i] = this->A[j];
            this->A[j] = tmp;
        }
        void expandArray(){
            value_type* newArray = (value_type*) malloc(2 * this->size * sizeof(value_type));
            for (int i = 0; i < this->size; ++i)
                newArray[i] = this->A[i];
            free(this->A);
            this->A = newArray;
            this->size *= 2;
        }
        static int parent(int n){
            return (n & 1) ? (n/2) : (n/2 - 1);
        }
        void heapify(int root){
            l = 2 * root + 1;
            r = l + 1;
            smallest = root;
            if ((l < this->n) && (comp(proj(this->A[l]), proj(this->A[smallest]))))
                smallest = l;
            if ((r < this->n) && (comp(proj(this->A[r]), proj(this->A[smallest]))))
                smallest = r;
            if (root != smallest){
                this->arraySwap(root, smallest);
                heapify(smallest);
            }
        }
};

#endif  // __HEAP_H