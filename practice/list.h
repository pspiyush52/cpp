#ifndef __LIST_H
#define __LIST_H

#include <iostream>
#include <initializer_list>

template<typename T>
struct _list_node{
    _list_node(const T& item):
        __data(item), __next(nullptr){}
    _list_node(T&& item):
        __data(static_cast<T&&>(item)), __next(nullptr){}
    _list_node(const T& item, _list_node* next):
        __data(item), __next(next){}
    _list_node(T&& item, _list_node* next):
        __data(static_cast<T&&>(item)), __next(next){}
    T __data;
    _list_node* __next;
};

template<typename T>
class List{
    public:
        typedef                             T            value_type;
        typedef                             T*           pointer;
        typedef                       const T*           const_pointer;
        typedef                             T&           reference;
        typedef                       const T&           const_reference;
        typedef         _list_node<value_type>           node;
    public:
        class _list_iterator{
            public:
                _list_iterator(node* ptr) : cur(ptr){}
                reference operator*(){
                    return cur->__data;
                }
                _list_iterator& operator++(){
                    this->cur = this->cur->__next;
                    return *this;
                }
                _list_iterator operator++(int){
                    this->cur = this->cur->__next;
                    return *this;
                }
                bool operator==(const _list_iterator& rhs) const{
                    return (this->cur == rhs.cur);
                }
                bool operator!=(const _list_iterator& rhs) const{
                    return (this->cur != rhs.cur);
                }
            private:
                node* cur;
        };
        class _const_list_iterator{
            public:
                _const_list_iterator(node* ptr) : cur(ptr){}
                const_reference operator*(){
                    return cur->__data;
                }
                _const_list_iterator& operator++(){
                    this->cur = this->cur->__next;
                    return *this;
                }
                _const_list_iterator operator++(int){
                    this->cur = this->cur->__next;
                    return *this;
                }
                bool operator==(const _const_list_iterator& rhs) const{
                    return (this->cur == rhs.cur);
                }
                bool operator!=(const _const_list_iterator& rhs) const{
                    return (this->cur != rhs.cur);
                }
            private:
                node* cur;
        };
    public:
        typedef _list_iterator iterator;
        typedef _const_list_iterator const_iterator;
        List() = default;
        List (std::initializer_list<T> args){
            auto iter = args.begin();
            auto end = args.end();
            for (; iter != end; ++iter)
                this->append(*iter);
        }
        List(const List& src){
            this->__copy__(src.__head, this->__head, this->__tail);
        }
        List(List&& src){
            this->__clear__(this->__head);
            this->__head = src.__head;
            this->__tail = src.__tail;
            src.invalidate();
        }
        List& operator=(const List& src){
            if (this == &src)
                return *this;
            this->__clear__(this->__head);
            this->__copy__(src.__head, this->__head, this->__tail);
            return *this;
        }
        List& operator=(List&& src){
            if (this == &src)
                return *this;
            this->__clear__(this->__head);
            this->__head = src.__head;
            this->__tail = src.__tail;
            src.invalidate();
            return *this;
        }
        List& append(const_reference item){
            node* new_node = new node(item);
            if (this->__head == nullptr)
                this->__head = new_node;
            else
                this->__tail->__next = new_node;
            this->__tail = new_node;
            return *this;
        }
        List& append(value_type&& item){
            node* new_node = new node(static_cast<value_type&&>(item));
            if (this->__head == nullptr)
                this->__head = new_node;
            else
                this->__tail->__next = new_node;
            this->__tail = new_node;
            return *this;
        }
        List& prepend(const_reference item){
            node* new_node = new node(static_cast<value_type&&>(item), this->__head);
            this->__head = new_node;
            return *this;
        }
        List& prepend(value_type&& item){
            node* new_node = new node(item, this->__head);
            this->__head = new_node;
            return *this;
        }
        iterator begin(){
            return iterator(this->__head);
        }
        iterator end(){
            return iterator(nullptr);
        }
        const_iterator begin() const{
            return const_iterator(this->__head);
        }
        const_iterator end() const{
            return const_iterator(nullptr);
        }
        const_iterator cbegin() const{
            return const_iterator(this->__head);
        }
        const_iterator cend() const{
            return const_iterator(nullptr);
        }
        friend std::ostream& operator<<(std::ostream& output, const List& L){
            if (L.__head){
                List::node* head = L.__head;
                List::node* tail = L.__tail;
                output.put('[');
                for (; head != tail; head = head->__next)
                    output << head->__data << ", ";
                output << tail->__data << ']';
            }
            else
                output << "[]";
            return output;
        }
        ~List(){
            this->__clear__(this->__head);
            this->__tail = nullptr;
        }
    private:
        node* __head{};
        node* __tail{};
        static void __copy__(node* head, node*& new_head, node*& new_tail){
            if (!head)
                return;
            new_head = new node(head->__data);
            new_tail = new_head;
            node* tmp{};
            for (head = head->__next; head; head = head->__next){
                tmp = new node(head->__data);
                new_tail->__next = tmp;
                new_tail = tmp;
            }
        }
        static void __clear__(node*& head){
            if (!head)
                return;
            node* tmp{};
            while (head){
                tmp = head->__next;
                delete head;
                head = tmp;
            }
            head = nullptr;
        }
        void invalidate(){
            this->__head = {};
            this->__tail = {};
        }
};

#endif  // __LIST_H