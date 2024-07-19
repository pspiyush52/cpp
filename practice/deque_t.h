#ifndef __DEQUE_T_H
#define __DEQUE_T_H

#include <iostream>
#include <initializer_list>
#include "exceptions.h"

template<typename T>
class deque{
    protected:
    const static size_t DEFAULT_SIZE{4};
    public:
        typedef T value_type;
        typedef value_type* pointer;
        typedef const value_type* const_pointer;
        typedef value_type& reference;
        typedef const value_type& const_reference;
    
    public:
        class iterator{
            public:
                iterator(size_t pos, deque* d) : __pos(pos), __d{d}{}
                reference operator*(){
                    return this->__d->__arr[this->__pos];
                }
                iterator& operator++(){
                    this->__pos = (this->__pos + 1) % this->__d->__size;
                    return *this;
                }
                iterator operator++(int){
                    iterator tmp{*this};
                    this->__pos = (this->__pos + 1) % this->__d->__size;
                    return tmp;
                }
                iterator& operator--(){
                    this->__pos = (this->__pos) ? (this->__pos - 1) : (this->__d->__front + this->__d->__n);
                    return *this;
                }
                iterator operator--(int){
                    const_iterator tmp{*this};
                    this->__pos = (this->__pos) ? (this->__pos - 1) : (this->__d->__size - 1);
                    return tmp;
                }
                iterator operator+(size_t i){

                }
                bool operator==(const iterator& rhs){
                    return (this->__pos == rhs.__pos);
                }
                bool operator!=(const iterator& rhs){
                    return (this->__pos != rhs.__pos);
                }
                size_t __get_pos(){
                    return this->__pos;
                }
            private:
                size_t __pos{};
                deque* __d{};
        };
        class const_iterator{
            public:
                const_iterator(size_t pos, const deque* d) : __pos(pos), __d(d){}
                const_reference operator*(){
                    return this->__d->__arr[this->__pos];
                }
                const_iterator& operator++(){
                    this->__pos = (this->__pos + 1) % this->__d->__size;
                    return *this;
                }
                const_iterator operator++(int){
                    const_iterator tmp{*this};
                    this->__pos = (this->__pos + 1) % this->__d->__size;
                    return tmp;
                }
                const_iterator operator--(){
                    this->__pos = (this->__pos) ? (this->__pos - 1) : (this->__d->__front + this->__d->__n);
                    return *this;
                }
                const_iterator operator--(int){
                    const_iterator tmp{*this};
                    this->__pos = (this->__pos) ? (this->__pos - 1) : (this->__d->__size - 1);
                    return tmp;
                }
                bool operator==(const const_iterator& rhs){
                    return (this->__pos == rhs.__pos);
                }
                bool operator!=(const const_iterator& rhs){
                    return (this->__pos != rhs.__pos);
                }
                size_t __rel_pos(){
                    if (this->__d->__front + this->__d->__n > this->__d->__size)
                        return (this->__pos - this->__d->__front + this->__d->__size);
                    else
                        return (this->__pos - this->__d->__front);
                }
            private:
                size_t __pos{};
                const deque* __d{};
        };
        class reverse_iterator{
            public:
                reverse_iterator(iterator&& iter) : it(iter){}
                reference operator*(){ return it.operator*(); }
                reverse_iterator operator++(){
                    --it;
                    return *this;
                }
                reverse_iterator operator++(int){
                    reverse_iterator tmp{*this};
                    --it;
                    return tmp;
                }
                reverse_iterator operator--(){
                    ++it;
                    return *this;
                }
                reverse_iterator operator--(int){
                    reverse_iterator tmp{*this};
                    ++it;
                    return tmp;
                }
                bool operator==(const reverse_iterator& rhs){
                    return (this->it == rhs.it);
                }
                bool operator!=(const reverse_iterator& rhs){
                    return (this->it != rhs.it);
                }
            private:
                iterator it;
        };
        class const_reverse_iterator{
            public:
                const_reverse_iterator(const_iterator&& iter) : it(iter){}
                const_reference operator*(){ return it.operator*(); }
                const_reverse_iterator& operator++(){
                    --it;
                    return *this;
                }
                const_reverse_iterator operator++(int){
                    auto tmp{it};
                    --it;
                    return tmp;
                }
                const_reverse_iterator operator--(){
                    ++it;
                    return *this;
                }
                const_reverse_iterator operator--(int){
                    auto tmp{it};
                    ++it;
                    return tmp;
                }
                bool operator==(const const_reverse_iterator& rhs){
                    return (this->it == rhs.it);
                }
                bool operator!=(const const_reverse_iterator& rhs){
                    return (this->it != rhs.it);
                }
            private:
                const_iterator it;
        };

    public:
        deque():
            __arr(new T[DEFAULT_SIZE]), __size(DEFAULT_SIZE){}
        deque(std::initializer_list<T> args){
            this->__size = (args.size() < DEFAULT_SIZE) ? DEFAULT_SIZE : 2 * args.size();
            this->__arr = new value_type[this->__size];
            this->__n = args.size();
            this->__front = 0;
            auto iter = args.begin();
            auto end = args.end();
            for (pointer ptr = this->__arr; iter != end; ++iter, ++ptr)
                *ptr = *iter;
        }
        deque(std::initializer_list<pointer> args){
            this->__make__(args.size());
            auto begin = args.begin();
            pointer ptr = this->__arr;
            for (; begin != args.end(); ++begin, ++ptr)
                *ptr = *(*begin);
            this->__n = args.size();
        }
        deque(const deque& src){
            if (src.is_empty())
                this->__make__();
            else{
                this->__make__(src.__size);
                const_iterator src_iter = src.cbegin(), src_end = src.cend();
                pointer ptr = this->__arr;
                for (; src_iter != src_end; ++src_iter, ++ptr)
                    *ptr = *src_iter;
                this->__n = src.__n;
            }
        }
        deque(deque&& src){
            if (src.is_empty())
                this->__make__();
            else{
                this->__arr = src.__arr;
                this->__size = src.__size;
                this->__front = src.__front;
                this->__n = src.__n;
                src.__invalidate__();
            }
        }
        deque& operator=(const deque& src){
            if (this == &src)
                return *this;
            delete[] this->__arr;
            this->__make__(src.__size);
            const_iterator src_iter = src.cbegin(), src_end = src.cend();
            pointer ptr = this->__arr;
            for (; src_iter != src_end; ++src_iter, ++ptr)
                *ptr = *src_iter;
            this->__n = src.__n;
            return *this;
        }
        deque& operator=(deque&& src){
            if (this == &src)
                return *this;
            delete[] this->__arr;
            this->__arr = src.__arr;
            this->__size = src.__size;
            this->__front = src.__front;
            this->__n = src.__n;
            src.__invalidate__();
            return *this;
        }
        deque& push_front(const_reference item){
            if (this->__is_full__())
                this->__expand__();
            this->__front = (this->__front) ? (this->__front - 1) : (this->__size - 1);
            this->__arr[this->__front] = item;
            ++this->__n;
            return *this;
        }
        deque& push_front(value_type&& item){
            if (this->__is_full__())
                this->__expand__();
            this->__front = (this->__front) ? (this->__front - 1) : (this->__size - 1);
            this->__arr[this->__front] = std::move(item);
            ++this->__n;
            return *this;
        }
        deque& push_back(const_reference item){
            if (this->__is_full__())
                this->__expand__();
            this->__arr[(this->__front + this->__n) % this->__size] = item;
            ++this->__n;
            return *this;
        }
        deque& push_back(value_type&& item){
            if (this->__is_full__())
                this->__expand__();
            this->__arr[(this->__front + this->__n) % this->__size] = std::move(item);
            ++this->__n;
            return *this;
        }
        deque& pop_front(){
            if (this->is_empty())
                throw ListEmpty("Cannot pop an item from an empty list");
            if (this->__vacant__())
                this->__shrink__();
            this->__front = (this->__front + 1) % this->__size;
            --this->__n;
            return *this;
        }
        deque& pop_frontn(int n){
            for (; (this->__n) && (n > 0); --n)
                this->pop_front();
            return *this;
        }
        deque& pop_back(){
            if (this->is_empty())
                throw ListEmpty("Cannot pop an item from an empty list");
            if (this->__vacant__())
                this->__shrink__();
            --this->__n;
            return *this;
        }
        deque& pop_backn(int n){
            for (; (this->__n) && (n > 0); --n)
                this->pop_back();
            return *this;
        }
        deque& shrink_to_fit(){
            if (!this->__n)
                return *this;
            pointer new_arr = new value_type[this->__n + 1], ptr = new_arr;
            for (auto& i : *this)
                *ptr++ = std::move(i);
            this->__arr = new_arr;
            this->__front = 0;
            this->__size = this->__n + 1;
            return *this;
        }
        const deque& shrink_to_fit() const {
            if (!this->__n)
                return *this;
            pointer new_arr = new value_type[this->__n + 1], ptr = new_arr;
            for (auto& i : *this)
                *ptr++ = std::move(i);
            this->__arr = new_arr;
            this->__front = 0;
            this->__size = this->__n + 1;
            return *this;
        }
        size_t size() const {
            return this->__n;
        }
        size_t capacity() const {
            return this->__size - 1;
        }
        bool is_empty() const {
            return !(this->__n);
        }
        iterator begin(){
            return iterator(this->__front, this);
        }
        iterator end(){
            return iterator((this->__front + this->__n) % this->__size, this);
        }
        const_iterator begin() const {
            return const_iterator(this->__front, this);
        }
        const_iterator end() const {
            return const_iterator((this->__front + this->__n) % this->__size, this);
        }
        const_iterator cbegin() const {
            return const_iterator(this->__front, this);
        }
        const_iterator cend() const {
            return const_iterator((this->__front + this->__n) % this->__size, this);
        }
        reverse_iterator rbegin(){
            return {{(this->__front + this->__n - 1) % this->__size, this}};
            
        }
        reverse_iterator rend(){
            if (this->__front)
                return {{(this->__front - 1) % this->__size, this}};
            return {{(this->__n), this}};
        }
        const_reverse_iterator rbegin() const {
            if (this->__n)
                return {{(this->__front + this->__n - 1) % this->__size, this}};
            return {{(this->__front), this}};
        }
        const_reverse_iterator rend() const {
            if (this->__front)
                return {{(this->__front - 1) % this->__size, this}};
            return {{(this->__n), this}};
        }
        const_reverse_iterator crbegin() const {
            return {{(this->__front + this->__n - 1) % this->__size, this}};
        }
        const_reverse_iterator crend() const {
            if (this->__front)
                return {{(this->__front - 1) % this->__size, this}};
            return {{(this->__front + this->__n), this}};
        }
        reference operator[](size_t i){
            if (i >= this->__n)
                throw IndexError();
            return this->__arr[(this->__front + i) % this->__size];
        }
        const_reference operator[](size_t i) const{
            if (i >= this->__n)
                throw IndexError();
            return this->__arr[(this->__front + i) % this->__size];
        }
        ~deque(){
            if (this->__arr){
                delete[] this->__arr;
                this->__invalidate__();
            }
        }
        friend std::ostream& operator<<(std::ostream& output, const deque& d){
            output.put('[');
            if (!d.is_empty()){
                for (size_t i{}; i < d.__n - 1; ++i)
                    output << d.__arr[(d.__front + i) % d.__size] << ", ";
                output << d.__arr[(d.__front + d.__n - 1) % d.__size];
            }
            output.put(']');
            return output;
        }
    protected:
        mutable T* __arr{};
        mutable size_t __size{};
        mutable size_t __front{};
        mutable size_t __n{};

        deque(size_t size){
            this->__make__(size);
        }
        deque(int, int, int){}
        bool __is_full__(){
            return ((this->__n + 1) >= this->__size);
        }
        bool __vacant__(){
            return ((this->__n - 1) <= (this->__size / 4));
        }
        void __make__(size_t size = DEFAULT_SIZE){
            if (size < this->DEFAULT_SIZE)
                size = DEFAULT_SIZE;
            this->__arr = new value_type[size];
            this->__size = size;
            this->__front = 0;
            this->__n = 0;
        }
        void __expand__(){
            pointer new_arr = new value_type[this->__size * 2];
            for (size_t i{}; i < this->__n; ++i)
                new_arr[i] = std::move(this->__arr[(this->__front + i) % this->__size]);
            delete[] this->__arr;
            this->__arr = new_arr;
            this->__size *= 2;
            this->__front = 0;
        }
        void __shrink__(){
            pointer new_arr = new value_type[this->__size / 2];
            for (size_t i{}; i <  this->__n; ++i)
                new_arr[i] = std::move(this->__arr[(this->__front + i) % this->__size]);
            delete[] this->__arr;
            this->__arr = new_arr;
            this->__size /= 2;
            this->__front = 0;
        }
        void __invalidate__(){
            this->__arr = {};
            this->__size = {};
            this->__front = {};
            this->__n = {};
        }
};

#endif  // __DEQUE_T_H
