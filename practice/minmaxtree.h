#ifndef __MIN_MAX_TREE
#define __MIN_MAX_TREE

#include <iostream>

template<typename Container>
class MinMaxTree {
    public:
        MinMaxTree(Container& cont):
        con{&cont}, internal{new Container(std::size(cont))}, n(std::size(cont)) {
            int j = 2 * n - 1;
            int i = j - 1;
            int k = n - 1;
            while (i > 1) {
                (*(this))[k] = Min((*(this))[i], (*(this))[j]);
                i -= 2;
                j -= 2;
                --k;
            }
            this->calcMins();
        }
        
        Container::value_type& operator[](int i) {
            if (i < this->n)
                return (*(this->internal))[i];
            else
                return (*(this->con))[i - this->n];
        }
        const Container::value_type& operator[](int i) const {
            if (i < this->n)
                return (*(this->internal))[i];
            else
                return (*(this->con))[i - this->n];
        }
        int getDataSize() {
            return this->n;
        }
        Container::value_type getMin() {
            return this->min;
        }
        Container::value_type getNextMin() {
            return this->nextMin;
        }

        
        ~MinMaxTree() {
            this->con = {};
            delete this->internal;
            this->internal = {};
            this->n = {};
        }
        template<typename U>
        friend std::ostream& operator<<(std::ostream& out, const MinMaxTree<U>& T);

    private:
        Container* con;
        Container* internal;
        int n;
        typename Container::value_type min;
        typename Container::value_type nextMin;

        static int Min(typename Container::value_type& x, typename Container::value_type& y) {
            return (x < y) ? x : y;
        }
        static int leftChild(int i) {
            return (2 * i);
        }
        static int rightChild(int i) {
            return (2*i + 1);
        }
        void calcMins() {
            this->min = (*this)[1];

            if ((*this)[2] == this->min)
                this->nextMin = (*this)[3];
            else
                this->nextMin = (*this)[2];
            int cur = 1, l, r, other;
            while (cur < this->n) {
                l = leftChild(cur);
                r = rightChild(cur);
                if ((*this)[l] == this->min) {
                    cur = l;
                    other = r;
                }
                else {
                    cur = r;
                    other = l;
                }
                this->nextMin = Min(this->nextMin, (*this)[other]);
            }
        }
};

template<typename U>
std::ostream& operator<<(std::ostream& out, const MinMaxTree<U>& T) {
    out << '[';
    if (T.n > 0) {
        int i{1};
        for (; i < 2 * T.n - 1; ++i)
            out << T[i] << ", ";
        out << T[i];
    }
    out << ']';
    return out;
}

#endif  // __MIN_MAX_TREE