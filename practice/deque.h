#ifndef __DEQUE_H
#define __DEQUE_H

#include <iostream>
#include <initializer_list>
#include <type_traits>
#include <concepts>
#include "reverse_iterator.h"
#include "exceptions.h"

template<typename T>
concept string_container = std::is_same_v<typename T::value_type, char> &&
requires (T item){
    item = " ";
    item + " ";
};

template<typename T>
class deque{
    
    private:
    class __deque_iterator{
        
        public:
            typedef        T         value_type;
            typedef        T*        pointer;
            typedef        T&        reference;
            typedef const  T&        const_reference;
            typedef long long        difference_type;
        
        public:
            __deque_iterator(size_t pos, deque* d) : __pos(pos), __parent(d){}
            __deque_iterator& operator++(){
                __parent->__incr(this->__pos);
                return *this;
            }
            __deque_iterator operator++(int){
                __parent->__incr(this->__pos);
                return *this;
            }
            __deque_iterator& operator--(){
                if (this->__pos)
                    --this->__pos;
                else{
                    this->__pos = __parent->__rear;
                }
                return *this;
            }
            __deque_iterator operator--(int){
                if (this->__pos)
                    --this->__pos;
                else{
                    this->__pos = __parent->__rear;
                }
                return *this;
            }
            value_type& operator*(){
                return (__parent->__arr[this->__pos]);
            }
            __deque_iterator operator+(size_t i){
                size_t rel_pos{this->__rel_pos()};
                rel_pos += i;
                if (rel_pos >= __parent->size())
                    this->__pos = __parent->__rear;
                else
                    this->__pos = (this->__pos + i) % __parent->__size;
                return *this;
            }
            __deque_iterator operator-(size_t i){
                size_t rel_pos{this->__rel_pos()};
                if (i > rel_pos)
                    this->__pos = __parent->__rear;
                else
                    this->__pos = (this->__pos + __parent->__size - i) % __parent->__size;
                return *this;
            }
            difference_type operator-(const __deque_iterator& rhs) const{
                return this->__rel_pos() - rhs.__rel_pos();
            }
            bool operator==(const __deque_iterator& rhs) const{
                return (this->__pos == rhs.__pos);
            }
            bool operator!=(const __deque_iterator& rhs) const{
                return (!(this->__pos == rhs.__pos));
            }
            size_t __get_pos(){
                return this->__pos;
            }
        
        private:
            size_t __pos{};
            deque* __parent{};

            size_t __rel_pos() const{
                if (this->__pos < __parent->__front)
                    return (this->__pos - __parent->__front + __parent->__size);
                else
                    return (this->__pos - __parent->__front);
            }
    };
    class __const_deque_iterator{

        public:
            typedef        T         value_type;
            typedef        T*        pointer;
            typedef        T&        reference;
            typedef  const T&        const_reference;
            typedef long long        difference_type;
        
        public:
            __const_deque_iterator(size_t pos, const deque* d) : __pos(pos), __parent(d){}
            __const_deque_iterator& operator++(){
                __parent->__incr(this->__pos);
                return *this;
            }
            __const_deque_iterator operator++(int){
                __parent->__incr(this->__pos);
                return *this;
            }
            __const_deque_iterator& operator--(){
                if (this->__pos)
                    --this->__pos;
                else{
                    this->__pos = __parent->__size - 1;
                }
                return *this;
            }
            __const_deque_iterator operator--(int){
                if (this->__pos)
                    --this->__pos;
                else{
                    this->__pos = __parent->__size - 1;
                }
                return *this;
            }
            const value_type& operator*() const{
                return (__parent->__arr[this->__pos]);
            }
            __const_deque_iterator operator+(size_t i){
                size_t rel_pos{this->__rel_pos()};
                rel_pos += i;
                if (rel_pos >= __parent->size())
                    this->__pos = __parent->__rear;
                else
                    this->__pos = (this->__pos + i) % __parent->__size;
                return *this;
            }
            __const_deque_iterator operator-(size_t i){
                size_t rel_pos{this->__rel_pos()};
                if (i > rel_pos)
                    this->__pos = __parent->__rear;
                else
                    this->__pos = (this->__pos + +__parent->__size - i) % __parent->__size;
                return *this;
            }
            difference_type operator-(const __const_deque_iterator& rhs) const{
                return this->__rel_pos() - rhs.__rel_pos();
            }
            bool operator==(const __const_deque_iterator& rhs) const{
                return (this->__pos == rhs.__pos);
            }
            bool operator!=(const __const_deque_iterator& rhs) const{
                return (!(this->__pos == rhs.__pos));
            }
            size_t __get_pos() const{
                return this->__pos;
            }
            size_t __rel_pos() const{
                if (this->__pos < __parent->__front)
                    return (this->__pos - __parent->__front + __parent->__size);
                else
                    return (this->__pos - __parent->__front);
            }
        private:
            size_t __pos{};
            const deque* __parent{};
    };

    public:
        typedef                                                           T                   value_type;
        typedef                                                           T*                  pointer;
        typedef                                                     const T*                  const_pointer;
        typedef                                                           T&                  reference;
        typedef                                                     const T&                  const_reference;
        typedef                                             __deque_iterator                  iterator;
        typedef                                       __const_deque_iterator                  const_iterator;
        typedef             __reverse_iterator<__deque_iterator, value_type>                  reverse_iterator;
        typedef __const_reverse_iterator<__const_deque_iterator, value_type>                  const_reverse_iterator;
    
    public:
        deque() : __arr(new value_type[SIZE]), __size(SIZE){}
        deque(long long size){
            this->__make(size);
        }
        deque(std::initializer_list<value_type> args) : deque(args.size() * 2){
            auto begin = args.begin();
            auto end = args.end();
            for (; begin != end; ++begin)
                this->push_back(*begin);
        }
        deque(std::initializer_list<pointer> args) : deque(args.size() * 2){
            auto begin = args.begin();
            auto end = args.end();
            for (; begin != end; ++begin)
                this->push_back(*(*begin));
        }
        deque(const_pointer arr, size_t size){
            this->__make(size);
            if (arr){
                const_pointer end = arr + size;
                for (; arr != end; ++arr)
                    this->push_back(*arr);
            }
        }
        template<typename Container>
        requires std::is_same_v<typename Container::value_type, value_type>
        deque(Container& con, size_t size){
            if (size > con.size())
                size = con.size();
            this->__make(size);
            for (auto iter = con.begin(), end = con.end(); iter != end; ++iter)
                this->push_back(*iter);
        }
        template<typename _iterator>
        requires std::is_same_v<typename _iterator::value_type, value_type>
        deque(_iterator& begin, _iterator& end){
            this->__make(end - begin + SIZE);
            for (; begin != end; ++begin)
                this->push_back(*begin);
        }
        template<typename _iterator>
        requires std::is_same_v<typename _iterator::value_type, value_type>
        deque(_iterator&& begin, _iterator&& end){
            this->__make(end - begin + SIZE);
            for (; begin != end; ++begin)
                this->push_back(*begin);
        }
        deque(const_pointer begin, const_pointer end){
            this->__make(2 * (end - begin));
            for (; begin != end; ++begin)
                this->push_back(*begin);
        }
        deque(const deque& src){
            if (src.is_empty()){
                this->__make(SIZE);
            }
            else{
                this->__make(src.__size);
                const_iterator src_iter = src.begin(), src_end = src.end();
                pointer iter = this->__arr;
                for (; src_iter != src_end; ++src_iter, ++iter)
                    *iter = *src_iter;
                this->__rear = src.size();
            }
        }
        deque(deque&& src){
            if (src.is_empty()){
                this->__make(SIZE);
                return;
            }
            delete[] this->__arr;
            this->__arr = src.__arr;
            this->__front = src.__front;
            this->__rear = src.__rear;
            this->__size = src.__size;
            src.__invalidate();
        }
        deque& operator=(const deque& src){
            if (this == &src)
                return *this;
            delete[] this->__arr;
            this->__make(src.__size);
            const_iterator src_iter = src.begin(), src_end = src.end();
            iterator iter = this->begin();
            for (; src_iter != src_end; ++src_iter, ++iter)
                *iter = *src_iter;
            this->__rear = src.size();
            return *this;
        }
        deque& operator=(deque&& src){
            if (this == &src)
                return *this;
            
            delete[] this->__arr;
            this->__arr = src.__arr;
            this->__front = src.__front;
            this->__rear = src.__rear;
            this->__size = src.__size;
            src.__invalidate();
            return *this;
        }
        bool is_empty() const{
            return (this->__front == this->__rear);
        }
        bool is_full() const{
            return (((this->__rear + 1) % this->__size) == this->__front);
        }
        size_t capacity() const{
            return (this->__size - 1);
        }
        size_t size() const{
            return ((this->__size + this->__rear - this->__front) % this->__size);
        }
        deque& push_front(const T& item){
            if (this->is_full())
                this->__expand();
            
            if (this->__front)
                --this->__front;
            else
                this->__front = this->__size - 1;
            this->__arr[this->__front] =  item;
            return *this;
        }
        deque& push_front(T&& item){
            if (this->is_full())
                this->__expand();
            
            if (this->__front)
                --this->__front;
            else
                this->__front = this->__size - 1;
            this->__arr[this->__front] = std::move(item);
            return *this;
        }
        deque& push_back(const T& item){
            if (this->is_full())
                this->__expand();
            
            this->__arr[this->__rear] =  item;
            this->__incr(this->__rear);
            return *this;
        }
        deque& push_back(T&& item){
            if (this->is_full())
                this->__expand();
            
            this->__arr[this->__rear] = std::move(item);
            this->__incr(this->__rear);
            return *this;
        }
        deque& pop_front(){
            if (this->is_empty()){
                return *this;
            }
            this->__incr(this->__front);
            return *this;
        }
        deque& pop_back(){
            if (this->is_empty()){
                return *this;
            }
            if (this->__rear)
                --this->__rear;
            else
                this->__rear = this->__size - 1;
            return *this;
        }
        deque& pop_frontn(int n){
            for(; !this->is_empty() && (n > 0); --n)
                this->pop_front();
            return *this;
        }
        deque& pop_backn(int n){
            for (; !is_empty() && (n > 0); --n)
                this->pop_back();
            return *this;
        }
        deque& shrink_to_fit(){
            this->__shrink();
            return *this;
        }
        const deque& shrink_to_fit() const{
            this->__shrink();
            return *this;
        }
        void clear(){
            this->__front = 0;
            this->__rear = 0;
        }
        iterator begin(){
            return iterator(this->__front, this);
        }
        iterator end(){
            return iterator(this->__rear, this);
        }
        const_iterator begin() const{
            return const_iterator(this->__front, this);
        }
        const_iterator end() const{
            return const_iterator(this->__rear, this);
        }
        const_iterator cbegin() const{
            return const_iterator(this->__front, this);
        }
        const_iterator cend() const{
            return const_iterator(this->__rear, this);
        }
        reverse_iterator rbegin(){
            iterator iter = this->end();
            return reverse_iterator(--iter);
        }
        reverse_iterator rend(){
            return reverse_iterator(this->end());
        }
        const_reverse_iterator rbegin() const{
            const_iterator iter = this->end();
            return const_reverse_iterator(--iter);
        }
        const_reverse_iterator rend() const{
            return const_reverse_iterator(this->end());
        }
        const_reverse_iterator crbegin() const{
            const_iterator iter = this->end();
            return const_reverse_iterator(--iter);
        }
        const_reverse_iterator crend() const{
            return const_reverse_iterator(this->end());
        }
        reference operator[](long long i){
            return (this->__arr[(this->__front + i) % this->__size]);
        }
        const_reference operator[](long long i) const{
            return (this->__arr[(this->__front + i) % this->__size]);
        }
        ~deque(){
            if (this->__arr){
                delete[] this->__arr;
                this->__invalidate();
            }
        }
        template<typename U>
        friend std::ostream& operator<<(std::ostream& output, const deque<U>& d);
        void __contents(){
            std::cout << *this;
            printf("\nArray size: %llu, Front: %llu, Rear: %llu", this->__size, this->__front, this->__rear);
        }

    protected:
        mutable pointer __arr{};
        mutable size_t __size{};
        mutable size_t __front{};
        mutable size_t __rear{};
        static const int SIZE{16};

        deque(int,int,int){}

        void __make(long long size){
            if (size < SIZE)
                size = SIZE;
            this->__arr = new value_type[size];
            this->__size = size;
            this->__front = this->__rear = 0;
        }
        void __expand(){
            pointer new_arr = new value_type[this->__size * 2], ptr = new_arr;
            for (iterator iter = this->begin(), end = this->end(); iter != end; ++iter)
                *ptr++ = *iter;
            delete[] this->__arr;
            this->__arr = new_arr;
            this->__front = 0;
            this->__rear = this->__size - 1;
            this->__size *= 2;
        }
        void __invalidate(){
            this->__arr = nullptr;
            this->__size = 0;
            this->__front = 0;
            this->__rear = 0;
        }
        void __incr(size_t& val) const{
            val = ((val + 1) % this->__size);
        }
        void __set_front(iterator iter){
            this->__front = iter.__get_pos();
        }
        void __set_front(const_iterator iter) const{
            this->__front = iter.__get_pos();
        }
        void __set_rear(iterator iter){
            this->__rear = iter.__get_pos();
        }
        void __set_rear(const_iterator iter) const{
            this->__rear = iter.__get_pos();
        }
        size_t __rel_pos(size_t i) const{
            if (i < this->__front)
                return (i - this->__front + this->__size);
            else
                return (i - this->__front);
        }
        void __shrink() const{
            if (this->is_full())
                return;
            size_t new_size = this->size() + 1;
            pointer arr = new value_type[new_size], ptr = arr;
            for (const_iterator iter = this->cbegin(), end = this->cend(); iter != end; ++iter, ++ptr)
                *ptr = *iter;
            delete[] this->__arr;
            this->__arr = arr;
            this->__front = 0;
            this->__rear = new_size - 1;
            this->__size = new_size;
        }
};

template<typename U>
std::ostream& operator<<(std::ostream& output, const deque<U>& d){
    if (d.is_empty()){
        output << "[]";
    }
    else{
        output << '[';
        typename deque<U>::const_iterator iter = d.begin(), before_end = d.end();
        --before_end;
        for (; iter != before_end; ++iter)
            output << *iter << ", ";
        output << *iter << ']';
    }
    return output;
}

template<string_container T>
requires string_container<T>
std::ostream& operator<<(std::ostream& output, const deque<T>& d){
    if (d.is_empty()){
        output << "[]";
    }
    else{
        output << '[';
        typename deque<T>::const_iterator iter = d.begin(), before_end = d.end();
        --before_end;
        for (; iter != before_end; ++iter)
            output << '"' << *iter << "\", ";
        output << '"' << *iter << "\"]";
    }
    return output;
}

#endif  // __DEQUE_H