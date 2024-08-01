#ifndef __HEAP_H
#define __HEAP_H

#include <iostream>

struct Less {
    template<typename T>
    bool operator()(const T& x, const T& y) const {
        return x < y;
    }
    template<typename T>
    bool operator()(T& x, T& y) {
        return x < y;
    }
};
struct Greater {
    template<typename T>
    bool operator()(const T& x, const T& y) const {
        return x > y;
    }
    template<typename T>
    bool operator()(T& x, T& y) {
        return x > y;
    }
};
struct Identity {
    template<typename T>
    const T& operator()(const T& x) const {
        return x;
    }
    template<typename T>
    T& operator()(T& x) {
        return x;
    }
};
template<typename Container, typename Comparator = Less, typename Projection = Identity>
class Heap {
    public:
        Heap(Container& container, const Comparator& compare = {}, const Projection& project = {}):
        H{container}, n(std::size(container)), comp{compare}, proj{project} {
            this->makeHeap();
        }
        int size() {
            return this->n;
        }
        bool isEmpty() {
            return (!this->n);
        }
        Heap& makeHeap() {
            for (int i = n/2 - 1; i >=0 ; --i)
                this->Heapify(i);
            return *this;
        }
        auto& getMin() {
            return this->H[0];
        }
        Heap& insert(const auto& item) {
            int p = this->parent(this->n), i = this->n;
            ++(this->n);
            H.push_back(item);
            while ((p >= 0) && comp(proj(this->H[i]), proj(this->H[p]))) {
                this->swap(i, p);
                i = p;
                p = this->parent(i);
            }
            return *this;
        }
        auto& extract() {
            --(this->n);
            this->swap(0, this->n);
            this->Heapify(0);
            return this->H[this->n];
        }
        Heap& sort() {
            // int s{this->n};
            while (this->n) {
                --(this->n);
                this->swap(0, this->n);
                this->Heapify(0);
            }
            // this->n = s;
            return *this;
        }

    private:
        Container& H;
        int n;
        const Comparator& comp;
        const Projection&  proj;

        int parent(int i) {
            return (i & 1) ? (i/2) : (i/2 - 1);
        }
        void swap(int i, int j) {
            auto tmp = std::move(this->H[i]);
            this->H[i] = std::move(this->H[j]);
            this->H[j] = std::move(tmp);
        }
        void Heapify(int root) {
            int min{root}, left{}, right{};
            while (root <= (n/2)) {
                left = 2*root + 1;
                right = left + 1;
                if (left < n && comp(proj(H[left]), proj(H[min])))
                    min = left;
                if (right < n && comp(proj(H[right]), proj(H[min])))
                    min = right;
                if (root != min)
                    swap(root, min);
                else
                    break;
                root = min;
            }
        }
};


#endif  // __HEAP_H