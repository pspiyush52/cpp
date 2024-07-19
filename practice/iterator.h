#ifndef __ITERATOR_H
#define __ITERATOR_H

#include <iostream>
#include <initializer_list>
#include <exception>
#include "stream_insertable.h"
#include "list_iterators.h"

class IndexError : public std::out_of_range{
    public:
        IndexError(const char* file, size_t line):
            std::out_of_range(""), filename(file), line_num(line){}
        const char* what() const noexcept{
            return "List index out of bounds";
        }
        void describe() const{
            std::cout << "\nIn file \"" << filename << "\",\nException occurred at "
                << "line: " << line_num << "\n  IndexError: " << what() << '\n';
        }
    
    private:
        const char* filename;
        size_t line_num;
};

template<typename T>
struct __list_node{
    __list_node(const T& data) : node_data(data), prev(nullptr), next(nullptr){}
    void fun(){}

    T node_data;
    __list_node* prev;
    __list_node* next;
};

template<typename T>
class List : public st::StreamInsertable<T>{

    typedef __list_node<T> node;

    public:
        typedef T value_type;
        typedef __list_iterator<T> iterator;
        typedef __clist_iterator<T> const_iterator;
        typedef __list_reverse_iterator<T> reverse_iterator;
        typedef __clist_reverse_iterator<T> const_reverse_iterator;

    public:
        List() = default;
        List(std::initializer_list<T> args);
        List(size_t size, const T& default_value);
        List(const List& src);
        List(List&& src);
        List& operator=(const List& src);
        List& operator=(List&& src);
        bool is_empty() const;
        List& prepend(const T& data);
        List& prepend(T&& data);
        List& append(const T& data);
        List& append(T&& data);
        List& pop_back();
        size_t size() const;
        List& reverse();
        iterator begin();
        iterator end();
        const_iterator end() const;
        const_iterator cbegin() const;
        const_iterator cend() const;
        reverse_iterator rbegin();
        reverse_iterator rend();
        const_reverse_iterator crbegin() const;
        const_reverse_iterator crend() const;
        T& operator[](size_t size);
        const T& operator[](size_t size) const;
        void empty();
        ~List();
    
    private:
        node* head{};
        node* tail{};
#ifndef NO_STORE_SIZE
        size_t list_size{};
#endif
        inline static T error{};
        
        void stream_insert(std::ostream& output) const;
        void stream_insert_s(std::ostream& output) const;
        void invalidate();
        void node_swap(node* x, node* y);
};

template<typename T>
List<T>::List(std::initializer_list<T> args) : List(){
#ifdef LIST_DEBUG
    std::cout << "List created at " << this << '\n';
#endif  // LIST_DEBUG
    if (args.size()){
        const T* begin = args.begin();
        const T* end = args.end();
        for (; begin != end; ++begin)
            this->append(*begin);
    }
}

template<typename T>
List<T>::List(size_t size, const T& default_value) : List(){
#ifdef LIST_DEBUG
    std::cout << "List created at " << this << '\n';
#endif  // LIST_DEBUG
    for (; size; --size)
        this->append(default_value);
}

template<typename T>
List<T>::List(const List<T>& src) : List(){
#ifdef LIST_DEBUG
    std::cout << "List created(copy) at " << this << " using list at " << &src << '\n';
#endif  // LIST_DEBUG
    const_iterator src_begin = src.begin();
    const_iterator src_end = src.end();
    for (; src_begin != src_end; ++src_begin)
        this->append(*src_begin);
}

template<typename T>
List<T>::List(List<T>&& src){
#ifdef LIST_DEBUG
    std::cout << "List created(move) at " << this << " using list at " << &src << '\n';
#endif  // LIST_DEBUG
    this->head = src.head;
    this->tail = src.tail;
#ifndef NO_STORE_SIZE
    this->list_size = src.list_size;
#endif
    src.invalidate();
}

template<typename T>
List<T>& List<T>::operator=(const List<T>& src){
    if (this == &src)
        return *this;

#ifdef LIST_DEBUG
    std::cout << "List at " << &src << " copy assigned to list at " << this << '\n';
#endif  // LIST_DEBUG
    this->empty();
    const_iterator begin = src.begin();
    const_iterator end = src.end();
    for (; begin != end; begin++)
        this->append(*begin);
    return *this;
}

template<typename T>
List<T>& List<T>::operator=(List<T>&& src){
    if (this == &src)
        return *this;
    
#ifdef LIST_DEBUG
    std::cout << "List at " << &src << " move assigned to list at " << this << '\n';
#endif  // LIST_DEBUG
    this->empty();
    this->head = src.head;
    this->tail = src.tail;
#ifndef NO_STORE_SIZE
    this->list_size = src.list_size;
#endif
    src.invalidate();
    return *this;
}

template<typename T>
bool List<T>::is_empty() const{
    return (head == nullptr);
}

template<typename T>
List<T>& List<T>::prepend(const T& data){
    __list_node<T>* new_node = new __list_node(data);
    if (!head)
        head = tail = new_node;
    else
    {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
#ifndef NO_STORE_SIZE
    list_size++;
#endif
    return *this;
}

template<typename T>
List<T>& List<T>::prepend(T&& data){
    __list_node<T>* new_node = new __list_node(data);
    if (!head)
        head = tail = new_node;
    else
    {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
#ifndef NO_STORE_SIZE
    list_size++;
#endif
    return *this;
}

template<typename T>
List<T>& List<T>::append(const T& data){
    __list_node<T>* new_node = new __list_node(data);
    if (head == nullptr)
        head = tail = new_node;
    else
    {
        new_node->prev = tail;
        tail->next = new_node;
        tail = new_node;
    }
#ifndef NO_STORE_SIZE
    list_size++;
#endif
    return *this;
}

template<typename T>
List<T>& List<T>::append(T&& data){
    __list_node<T>* new_node = new __list_node(data);
    if (head == nullptr)
        head = tail = new_node;
    else
    {
        new_node->prev = tail;
        tail->next = new_node;
        tail = new_node;
    }
#ifndef NO_STORE_SIZE
    list_size++;
#endif
    return *this;
}

template<typename T>
List<T>& List<T>::pop_back(){
    if (this->is_empty())
        return *this;
    
    if (head == tail){
        delete head;
        this->invalidate();
        return *this;
    }
    __list_node<T>* tmp = this->tail->prev;
    tmp->next = nullptr;
    delete this->tail;
    this->tail = tmp;

#ifndef NO_STORE_SIZE
    this->list_size--;
#endif
    return *this;
}

template<typename T>
size_t List<T>::size() const{
#ifndef NO_STORE_SIZE
    return list_size;
#else
    size_t count{};
    List<T>::const_iterator begin = cbegin();
    List<T>::const_iterator end = cend();
    for (; begin != end; ++begin)
        ++count;
    return count;
#endif  // NO_STORE_SIZE
}

template<typename T>
List<T>& List<T>::reverse(){    
    node* cur = head;
    node_swap(head, tail);
    node* next_node;
    while (cur){
        next_node = cur->next;
        node_swap(cur->prev, cur->next);
        cur = next_node;
    }
    
    return *this;
}

template<typename T>
void List<T>::stream_insert(std::ostream& output) const{
    if (!head)
        output << "[()";
    else
    {
        output << "[(";
        node* tmp = head;
        for (; tmp->next; tmp = tmp->next)
            output << tmp->node_data << ", ";
        output << tmp->node_data << ')';
    }
    output << ", <List object at " << this << ">]";
}

template<typename T>
void List<T>::stream_insert_s(std::ostream& output) const{
    if (!head)
        output << "[()";
    else
    {
        output << "[(";
        node* tmp = head;
        for (; tmp->next; tmp = tmp->next)
            output << '"' << tmp->node_data << "\", ";
        output << '"' << tmp->node_data << "\")";
    }
    output << ", <List object at " << this << ">]";
}

template<typename T>
void List<T>::invalidate(){
    head = tail = nullptr;
#ifndef NO_STORE_SIZE
    list_size = 0;
#endif
}

template<typename T>
List<T>::~List(){
#ifdef LIST_DEBUG
    std::cout << "List at " << this << " destroyed.\n";
#endif  // LIST_DEBUG
    if (head){
        node* tmp = head;
        while (head){
            tmp = head->next;
            delete head;
            head = tmp;
        }
#ifndef NO_STORE_SIZE
        list_size = 0;
#endif
    }
}

template<typename T>
__list_iterator<T> List<T>::begin(){
    return __list_iterator<T>(head);
}
template<typename T>
__list_iterator<T> List<T>::end(){
    return __list_iterator<T>();
}
template<typename T>
__clist_iterator<T> List<T>::end() const{
    return __clist_iterator<T>();
}
template<typename T>
__clist_iterator<T> List<T>::cbegin() const{
    return __clist_iterator<T>(head);
}
template<typename T>
__clist_iterator<T> List<T>::cend() const{
    return __clist_iterator<T>();
}
template<typename T>
__list_reverse_iterator<T> List<T>::rbegin(){
    return __list_reverse_iterator<T>(tail);
}
template<typename T>
__list_reverse_iterator<T> List<T>::rend(){
    return __list_reverse_iterator<T>();
}
template<typename T>
__clist_reverse_iterator<T> List<T>::crbegin() const{
    return __clist_reverse_iterator<T>(tail);
}
template<typename T>
__clist_reverse_iterator<T> List<T>::crend() const{
    return __clist_reverse_iterator<T>();
}

template<typename T>
T& List<T>::operator[](size_t pos){

#ifndef NO_STORE_SIZE
    if (pos > (list_size - 1))
        throw IndexError{__FILE__, __LINE__};
#endif    
    
    iterator begin = this->begin();
    iterator end = this->end();
    for (size_t i{}; begin != end; ++i, ++begin)
        if (i == pos)
            return *begin;
    
    return error;
}

template<typename T>
const T& List<T>::operator[](size_t pos) const{

#ifndef NO_STORE_SIZE
    if (pos > (list_size - 1))
        throw IndexError{__FILE__, __LINE__};
#endif
    
    const_iterator begin = this->begin();
    const_iterator end = this->end();
    for (size_t i{}; begin != end; ++i, ++begin)
        if (i == pos)
            return *begin;
    
    return error;
}

template<typename T>
void List<T>::empty(){
    if (!head)
        return;
    node* tmp = head;
    while (head){
        tmp = head->next;
        delete head;
        head = tmp;
    }
    invalidate();
}

template<typename T>
void List<T>::node_swap(node* x, node* y){
    node* tmp = x;
    x = y;
    y = tmp;
}

#endif  // __ITERATOR_H