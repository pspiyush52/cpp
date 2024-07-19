#ifndef __DEQUE_H
#define __DEQUE_H

#include <iostream>
#include <stdlib.h>
#include <initializer_list>

template<typename T>
class deque {
    static const int DEFAULT_SIZE{8};
    public:
        typedef                T                value_type;
        typedef                T*               pointer;
        typedef                T&               reference;
    
    public:
        class iterator {
            public:
                iterator(deque* p, int i): par(p), pos(i) {}
                T& operator*() {
                    return (par->arr[this->pos]);
                }
                void operator++() {
                    pos = ((pos + 1) % (par->arr_size + 1));
                }
                bool operator==(const iterator& rhs) {
                    return (this->pos == rhs.pos);
                }
                bool operator!=(const iterator& rhs) {
                    return (this->pos != rhs.pos);
                }
            private:
                deque* par;
                int pos;
        };
    public:
        deque() {
            this->make();
        }
        deque(int size) {
            this->make(size);
        }
        deque(std::initializer_list<T> args) {
            this->make(args.size() * 2);
            auto iter = args.begin();
            for (; iter != args.end(); ++iter)
                this->push_back(*iter);
        }
        bool isEmpty() const {
            return (!this->cur);
        }
        bool isFull() const {
            return (this->cur == this->arr_size);
        }
        constexpr int size() const {
            return this->cur;
        }
        constexpr int capacity() const {
            return this->arr_size;
        }

        deque& push_front(const T& item) {
            if (this->isFull())
                this->expand();
            this->front = (this->front) ? (this->front - 1) : (this->arr_size);
            this->arr[this->front] = item;
            ++(this->cur);
            return *this;
        }
        deque& push_back(const T& item) {
            if (this->isFull())
                this->expand();
            this->arr[(this->front + this->cur) % (this->arr_size + 1)] = item;
            ++(this->cur);
            return *this;
        }
        void pop_front() {
            if (this->isEmpty())
                return;
            this->front = (this->front == this->arr_size) ? 0 : (this->front + 1);
            --(this->cur);
        }
        void pop_back() {
            if (this->isEmpty())
                return;
            --(this->cur);
        }

        iterator begin() {
            return iterator(this, this->front);
        }
        iterator end() {
            return iterator(this, (this->front + this->cur) % (this->arr_size + 1));
        }

        T& operator[](int i) {
            return this->arr[(this->front + i) % (this->arr_size + 1)];
        }

        // DBG
        void status() {
            printf("(Front: %d, Rear: %d, Cur: %d, size: %d)\n", front, (front + cur) % (arr_size + 1), cur, arr_size);
        }
        void array() {
            std::cout << '[';
            for (int i{}; i < this->arr_size; ++i)
                std::cout << this->arr[i] << ", ";
            std::cout << this->arr[this->arr_size] << ']';
        }

        ~deque() {
            delete[] this->arr;
            this->invalidate();
        }
        template<typename U>
        friend inline std::ostream& operator<<(std::ostream& out, const deque<U>& d);

    private:
        T* arr;
        int front;
        int cur;
        int arr_size;
    
    void set(T* _arr, int _front, int _cur, int _arr_size) {
        this->arr = _arr;
        this->front = _front;
        this->cur = _cur;
        this->arr_size = _arr_size;
    }
    void make(int _size = DEFAULT_SIZE) {
        _size = (_size < DEFAULT_SIZE) ? DEFAULT_SIZE : _size;
        this->set(new T[_size + 1], 0, 0, _size);
    }
    void expand() {
        T* new_arr = new T[2 * this->arr_size + 1];
        iterator iter = this->begin();
        for (int i{}; i < this->arr_size; ++i, ++iter)
            new_arr[i] = *iter;
        delete[] this->arr;
        this->set(new_arr, 0, this->cur, this->arr_size * 2);
    }
    void invalidate() {
        this->set({}, {}, {}, {});
    }
};

template<typename U>
std::ostream& operator<<(std::ostream& out, const deque<U>& d) {
    out << '[';
    if (!d.isEmpty()) {
        int i{d.front}, count{};
        for (; count < d.cur - 1; ++count, i = (i + 1) % (d.arr_size + 1))
            out << d.arr[i] << ", ";
        out << d.arr[i];
    }
    out << ']';
    return out;
}

#endif  // __DEQUE_H