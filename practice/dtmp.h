#ifndef __DEQUE_H
#define __DEQUE_H

#include <iostream>
#include <initializer_list>
#include <type_traits>
#include <concepts>
#include "reverse_iterator.h"
#include "exceptions.h"

#define STD_OSR std::ostream&

template<typename T>
concept string_like = std::is_same_v<typename T::value_type, char> &&
requires (T item){
    item = " ";
    item + " ";
};

template<typename T>
class deque{
    
    private:
    static const int SIZE{16};
    class __deque_iterator{
        
        public:
            typedef       T         value_type;
            typedef       T*        pointer;
            typedef       T&        reference;
            typedef const T&        const_reference;
        
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
                    this->__pos = __parent->__size - 1;
                }
                return *this;
            }
            __deque_iterator operator--(int){
                if (this->__pos)
                    --this->__pos;
                else{
                    this->__pos = __parent->__size - 1;
                }
                return *this;
            }
            T& operator*(){
                return (__parent->__arr[this->__pos]);
            }
            __deque_iterator operator+(size_t i){
                if (i >= __parent->size())
                    this->__pos = __parent->__rear;
                else
                    this->__incr_set(i);
                return *this;
            }
            __deque_iterator operator-(size_t i){
                if (i >= __parent->size())
                    this->__pos = __parent->__rear;
                else
                    this->__incr_set(__parent->__size - i);
                return *this;
            }
            std::strong_ordering operator<=>(const __deque_iterator& rhs) const{
                using so = std::strong_ordering;
                if (__parent->__front < __parent->__rear){
                    if (this->__pos < rhs.__pos)
                        return so::less;
                    else if (this->pos > rhs.__pos)
                        return so::greater;
                    else
                        return so::equal;
                }
                else{
                    if (this->__pos < rhs.__pos)
                        return so::greater;
                    else if (this->pos > rhs.__pos)
                        return so::less;
                    else
                        return so::equal;
                }
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

            void __incr_set(size_t i){
                this->__pos = (this->__pos + i) % __parent->__size;
                if (__parent->__front < __parent->__rear){
                    if (this->__pos >= __parent->__rear || this->__pos < __parent->__front)
                        this->__pos = __parent->__rear;
                }
                else{
                    if (this->__pos >= __parent->__rear && this->__pos < __parent->__front)
                        this->__pos = __parent->__rear;
                }
            }
    };
    class __const_deque_iterator{

        public:
            typedef       T         value_type;
            typedef       T*        pointer;
            typedef       T&        reference;
            typedef const T&        const_reference;
        
        public:
            __const_deque_iterator(size_t pos, const deque* d) : __pos(pos), __parent(d){}
            __const_deque_iterator& operator++(){
                __parent->__incr(this->__pos);
                return *this;
            }
            __const_deque_iterator operator++(int){
                __parent->incr(this->__pos);
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
            const T& operator*() const{
                return (__parent->__arr[this->__pos]);
            }
            __const_deque_iterator operator+(size_t i){
                if (i >= __parent->size())
                    this->__pos = __parent->__rear;
                else
                    this->__incr_set(i);
                return *this;
            }
            __const_deque_iterator operator-(size_t i){
                if (i >= __parent->size())
                    this->__pos = __parent->__rear;
                else
                    this->__incr_set(__parent->__size - i);
                return *this;
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
        private:
            size_t __pos{};
            const deque* __parent{};

            void __incr_set(size_t i){
                this->__pos = (this->__pos + i) % __parent->__size;
                if (__parent->__front < __parent->__rear){
                    if (this->__pos > __parent->__rear || this->__pos < __parent->__front)
                        this->__pos = __parent->__rear;
                }
                else{
                    if (this->__pos >= __parent->__rear && this->__pos < __parent->__front)
                        this->__pos = __parent->__rear;
                }
            }
    };
    class __modifier{
        public:
            __modifier(const T& item) : __item(item){}
            __modifier(const T& item, char c) : __item(item), ch(c){}
            friend STD_OSR operator<<(STD_OSR output, const __modifier& m){
                if (m.ch)
                    output << m.ch << m.__item << m.ch;
                else
                    output << m.__item;
                return output;
            }
        private:
            const T& __item;
            char ch{};
    };
    public:
        typedef                                                             T                   value_type;
        typedef                                                             T*                  pointer;
        typedef                                                             T&                  reference;
        typedef                                                       const T&                  const_reference;
        typedef                                             __deque_iterator                  iterator;
        typedef                                       __const_deque_iterator                  const_iterator;
        typedef             __reverse_iterator<__deque_iterator, value_type>                  reverse_iterator;
        typedef __const_reverse_iterator<__const_deque_iterator, value_type>                  const_reverse_iterator;
    
    public:
        deque() : __arr(new T[SIZE]), __size(SIZE){}
        deque(std::initializer_list<T> args) : deque(args.size() * 2){
            auto begin = args.begin();
            auto end = args.end();
            for (; begin != end; ++begin)
                this->push_back(*begin);
        }
        deque(std::initializer_list<T*> args) : deque(args.size() * 2){
            auto begin = args.begin();
            auto end = args.end();
            for (; begin != end; ++begin)
                this->push_back(*(*begin));
        }
        deque(const T* arr, size_t size){
            if (size < SIZE)
                this->__make(SIZE);
            else
                this->__make(size);
            if (arr){
                const T* end = arr + size;
                for (; arr != end; ++arr)
                    this->push_back(*arr);
            }
        }
        template<typename _iterator>
        requires std::is_same_v<typename _iterator::value_type, value_type>
        deque(_iterator& begin, _iterator& end){
            this->__make(SIZE);
            for (; begin != end; ++begin)
                this->push_back(*begin);
        }
        template<typename _iterator>
        requires std::is_same_v<typename _iterator::value_type, value_type>
        deque(_iterator&& begin, _iterator&& end){
            this->__make(SIZE);
            for (; begin != end; ++begin)
                this->push_back(*begin);
        }
        deque(const T* begin, const T* end){
            long long size = end - begin, dsize{2 * size};
            if (dsize < SIZE)
                this->__make(SIZE);
            else
                this->__make(dsize);
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
                T* iter = this->__arr;
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
            this->__arr[this->__front] = item;
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
            
            this->__arr[this->__rear] = item;
            this->__incr(this->__rear);
            return *this;
        }
        deque& pop_front(){
            if (this->is_empty()){
                std::cout << "Empty\n";
                return *this;
            }
            this->__incr(this->__front);
            return *this;
        }
        deque& pop_back(){
            if (this->is_empty()){
                std::cout << "Empty\n";
                return *this;
            }
            if (this->__rear)
                --this->__rear;
            else
                this->__rear = this->__size - 1;
            return *this;
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
            iterator iter = this->begin();
            return reverse_iterator(--iter);
        }
        const_reverse_iterator rbegin() const{
            const_iterator iter = this->end();
            return const_reverse_iterator(--iter);
        }
        const_reverse_iterator rend() const{
            const_iterator iter = this->begin();
            return const_reverse_iterator(--iter);
        }
        const_reverse_iterator crbegin() const{
            const_iterator iter = this->end();
            return const_reverse_iterator(--iter);
        }
        const_reverse_iterator crend() const{
            const_iterator iter = this->begin();
            return const_reverse_iterator(--iter);
        }
        ~deque(){
            delete[] this->__arr;
            this->__invalidate();
        }
        template<typename U>
        friend STD_OSR operator<<(STD_OSR output, const deque<U>& d);

    protected:
        T* __arr{};
        size_t __size{};
        size_t __front{};
        size_t __rear{};

        deque(size_t size){
            if (size < SIZE)
                size = SIZE;
            this->__make(size);
        }

        void __make(size_t size){
            this->__arr = new T[size];
            this->__size = size;
            this->__front = this->__rear = 0;
        }
        void __expand(){
            T* new_arr = new T[this->__size * 2], *ptr = new_arr;
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
        void __clear(){
            delete[] this->__arr;
            this->__invalidate();
        }
        void __incr(size_t& val) const{
            val = ((val + 1) % this->__size);
        }
        void __contents(){
            std::cout << '[';
            size_t i{}, upto{this->__size - 1};
            for (size_t i{}; i < upto; ++i)
                printf("(%d: '%c'), ", this->__arr[i], this->__arr[i]);
            printf("(%d: %c)]", this->__arr[i], this->__arr[i]);
            std::cout << "Arr size: " << this->__size << ", front: " << this->__front << ", rear: " << this->__rear;
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
};

template<typename U>
STD_OSR operator<<(STD_OSR output, const deque<U>& d){
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

template<typename T>
requires string_like<T>
STD_OSR operator<<(STD_OSR output, const deque<T>& d){
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