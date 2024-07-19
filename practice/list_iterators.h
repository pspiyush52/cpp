#ifndef __LIST_ITERATORS_H
#define __LIST_ITERATORS_H

template<typename T>
class __list_node;

template<typename T>
class __list_iterator{
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using reference = value_type&;
        using pointer = value_type*;
        using difference_type = std::ptrdiff_t;
    
    public:
        __list_iterator() = default;
        explicit __list_iterator(__list_node<T>* node_ptr):
            ptr(node_ptr){}
        __list_iterator(const __list_iterator& src) = default;
        __list_iterator& operator++(){
            ptr = ptr->next;
            return *this;
        }
        __list_iterator operator++(int){
            __list_iterator tmp(*this);
            ptr = ptr->next;
            return tmp;
        }
        T& operator*() const{
            return ptr->node_data;
        }
        __list_node<T>* operator->(){
            return ptr;
        }
        bool operator==(const __list_iterator& rhs) const = default;
    
    private:
        __list_node<T>* ptr{};
};

template<typename T>
class __list_reverse_iterator{
    public:
        __list_reverse_iterator() = default;
        explicit __list_reverse_iterator(__list_node<T>* node_ptr):
            ptr(node_ptr){}
        __list_reverse_iterator(const __list_reverse_iterator& src) = default;
        __list_reverse_iterator& operator++(){
            ptr = ptr->prev;
            return *this;
        }
        __list_reverse_iterator operator++(int){
            __list_reverse_iterator tmp(*this);
            ptr = ptr->prev;
            return tmp;
        }
        T& operator*(){
            return ptr->node_data;
        }
        bool operator==(const __list_reverse_iterator& rhs) const = default;
    
    private:
        __list_node<T>* ptr{};
};


template<typename T>
class __clist_iterator{
    public:
        __clist_iterator() = default;
        explicit __clist_iterator(__list_node<T>* node_ptr):
            ptr(node_ptr){}
        __clist_iterator(const __clist_iterator& src) = default;
        __clist_iterator& operator++(){
            ptr = ptr->next;
            return *this;
        }
        __clist_iterator operator++(int){
            __clist_iterator tmp(*this);
            ptr = ptr->next;
            return tmp;
        }
        const T& operator*() const{
            return ptr->node_data;
        }
        bool operator==(const __clist_iterator& rhs) const = default;
    
    private:
        __list_node<T>* ptr{};
};

template<typename T>
class __clist_reverse_iterator{
    public:
        __clist_reverse_iterator() = default;
        explicit __clist_reverse_iterator(__list_node<T>* node_ptr):
            ptr(node_ptr){}
        __clist_reverse_iterator(const __clist_reverse_iterator& src) = default;
        __clist_reverse_iterator& operator++(){
            ptr = ptr->prev;
            return *this;
        }
        __clist_reverse_iterator operator++(int){
            __clist_reverse_iterator tmp(*this);
            ptr = ptr->prev;
            return tmp;
        }
        const T& operator*() const{
            return ptr->node_data;
        }
        bool operator==(const __clist_reverse_iterator& rhs) const = default;
    
    private:
        __list_node<T>* ptr{};
};

#endif  // __LIST_ITERATORS_H