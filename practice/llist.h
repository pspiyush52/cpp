#ifndef __LLIST_H
#define __LLIST_H

#include <iostream>
#include <initializer_list>

template<typename T>
struct __list_node {
    __list_node(const T& k): key(k), prev(nullptr), next(nullptr) {}
    __list_node(const T& k, __list_node* p, __list_node* n): key(k), prev(p), next(n) {}
    __list_node(T&& k): key(std::move(k)), prev(nullptr), next(nullptr) {}
    __list_node(T&& k, __list_node* p, __list_node* n): key(std::move(k)), prev(p), next(n) {}
    T key;
    __list_node* prev;
    __list_node* next;
};

template<typename T>
class LList {
    typedef __list_node<T>  ListNode;
    public:
        class iterator {
            public:
                iterator(__list_node<T>* p): cur(p) {}
                T& operator*() {
                    return (this->cur->key);
                }
                iterator& operator++() {
                    this->cur = this->cur->next;
                    return *this;
                }
                iterator& operator--() {
                    this->cur = this->cur->prev;
                    return *this;
                }
                bool operator==(const iterator& rhs) const {
                    return (this->cur == rhs.cur);
                }
                bool operator!=(const iterator& rhs) const {
                    return (this->cur != rhs.cur);
                }
                __list_node<T>* get_pointer() const {
                    return this->cur;
                }
            private:
                __list_node<T>* cur;
        };
        class const_iterator {
            public:
                const_iterator(__list_node<T>* p): cur(p) {}
                const T& operator*() {
                    return this->cur->key;
                }
                const_iterator& operator++() {
                    this->cur = this->cur->next;
                    return *this;
                }
                const_iterator& operator--() {
                    this->cur = this->cur->prev;
                    return *this;
                }
                bool operator==(const const_iterator& rhs) const {
                    return (this->cur == rhs.cur);
                }
                bool operator!=(const const_iterator& rhs) const {
                    return (this->cur != rhs.cur);
                }
            private:
                __list_node<T>* cur;
        };
        class reverse_iterator {
            public:
                reverse_iterator(__list_node<T>* p): cur(p) {}
                T& operator*() {
                    return this->cur->key;
                }
                reverse_iterator& operator++() {
                    this->cur = this->cur->prev;
                    return *this;
                }
                reverse_iterator& operator--() {
                    this->cur = this->cur->next;
                    return *this;
                }
                bool operator==(const reverse_iterator& rhs) const {
                    return (this->cur == rhs.cur);
                }
                bool operator!=(const reverse_iterator& rhs) const {
                    return (this->cur != rhs.cur);
                }
            private:
                __list_node<T>* cur;
        };
        class const_reverse_iterator {
            public:
                const_reverse_iterator(__list_node<T>* p): cur(p) {}
                const T& operator*() {
                    return this->cur->key;
                }
                const_reverse_iterator& operator++() {
                    this->cur = this->cur->prev;
                    return *this;
                }
                const_reverse_iterator& operator--() {
                    this->cur = this->cur->next;
                    return *this;
                }
                bool operator==(const const_reverse_iterator& rhs) const {
                    return (this->cur == rhs.cur);
                }
                bool operator!=(const const_reverse_iterator& rhs) const {
                    return (this->cur != rhs.cur);
                }
            private:
                __list_node<T>* cur;
        };
        LList() {
            this->head = new ListNode({});
            this->tail = new ListNode({}, this->head, nullptr);
            this->head->next = this->tail;
            this->n = {};
        }
        LList(const std::initializer_list<T>& args): LList() {
            auto iter = args.begin();
            for (; iter != args.end(); ++iter)
                this->append(*iter);
        }
        LList(const LList& src): LList() {
            const_iterator it = src.begin();
            for (; it != src.end(); ++it)
                this->append(*it);
        }
        LList(LList&& src) {
            this->head = src.head;
            this->tail = src.tail;
            this->n = src.n;
            src.invalidate();
        }
        LList& operator=(const LList& src) = delete;
        LList& operator=(LList&& src) = delete;

        bool isEmpty() const {
            return (!this->n);
        }
        int size() const {
            return this->n;
        }
        LList& append(const T& item) {
            return this->_append(new ListNode(item, this->tail->prev, this->tail));
        }
        LList& append(T&& item) {
            return this->_append(new ListNode(std::forward<T>(item), this->tail->prev, this->tail));
        }
        LList& prepend(const T& item) {
            return this->_prepend(new ListNode(item, this->head, this->head->next));
        }
        LList& prepend(T&& item) {
            return this->_prepend(new ListNode(std::forward<T>(item), this->head, this->head->next));
        }
        LList& push_front(const T& item) {
            return this->prepend(std::forward<T>(item));
        }
        LList& push_back(const T& item) {
            return this->append(std::forward<T>(item));
        }
        bool pop_front() {
            if (this->isEmpty())
                return false;
            ListNode* tmp = this->head->next;
            tmp->next->prev = this->head;
            this->head->next = tmp->next;
            delete tmp;
            --(this->n);
            return true;
        }
        bool pop_back() {
            if (this->isEmpty())
                return false;
            ListNode* tmp = this->tail->prev;
            tmp->prev->next = this->tail;
            this->tail->prev = tmp->prev;
            delete tmp;
            --(this->n);
            return true;
        }
        iterator find(const T& key) {
            iterator it = this->begin();
            for (; it != this->end(); ++it)
                if (*it == key)
                    return it;
            return this->end();
        }
        bool in(const T& key) const {
            const_iterator it = this->cbegin();
            for (; it != this->cend(); ++it)
                if (*it == key)
                    return true;
            return false;
        }
        LList& insert_before(const iterator& it, const T& val) {
            if (it == this->end())
                return *this;
            ListNode* cur = it.get_pointer();
            ListNode* newNode = new ListNode(val, cur->prev, cur);
            cur->prev->next = newNode;
            cur->prev = newNode;
            ++(this->n);
            return *this;
        }
        LList& insert_before(const T& key, const T& val) {
            return this->insert_before(this->find(key), val);
        }
        LList& insert_after(const iterator& it, const T& val) {
            if (it == this->end())
                return *this;
            ListNode* cur = it.get_pointer();
            ListNode* newNode = new ListNode(val, cur, cur->next);
            cur->next->prev = newNode;
            cur->next = newNode;
            ++(this->n);
            return *this;
        }
        LList& insert_after(const T& key, const T& val) {
            return this->insert_after(this->find(key), val);
        }
        bool remove(const T& key) {
            iterator it = this->find(std::forward<const T>(key));
            if (it == this->end())
                return false;
            ListNode* cur = it.get_pointer();
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
            delete cur;
            --(this->n);
            return true;
        }
        LList& sort() {
            this->insertionSort(this->head->next);
            return *this;
        }
        LList& reverse() {
            if (!this->isEmpty()) {
                ListNode* cur = this->head;
                for (; cur != this->tail; cur = cur->prev)
                    this->node_swap(cur->prev, cur->next);
                this->node_swap(cur->prev, cur->next);
                this->node_swap(this->head, this->tail);
            }
            return *this;
        }
        
        iterator begin() {
            return {this->head->next};
        }
        iterator end() {
            return {this->tail};
        }
        const_iterator begin() const {
            return {this->head->next};
        }
        const_iterator end() const {
            return {this->tail};
        }
        const_iterator cbegin() const {
            return {this->head->next};
        }
        const_iterator cend() const {
            return {this->tail};
        }

        reverse_iterator rbegin() {
            return {this->tail->prev};
        }
        reverse_iterator rend() {
            return {this->head};
        }
        const_reverse_iterator rbegin() const {
            return {this->tail->prev};
        }
        const_reverse_iterator rend() const {
            return {this->head};
        }
        const_reverse_iterator crbegin() const {
            return {this->tail->prev};
        }
        const_reverse_iterator crend() const {
            return {this->head};
        }
        
        ~LList() {
            this->deleteList();
            this->invalidate();
        }

        template<typename U>
        friend std::ostream& operator<<(std::ostream& out, const LList<U>& A);

    private:
        ListNode* head{};
        ListNode* tail{};
        int n{};

        void insertionSort(ListNode* h) {
            if (h != this->tail) {
                insertionSort(h->next);
                T key = h->key;
                for (; h->next != this->tail && h->next->key < key; h = h->next)
                    h->key = h->next->key;
                h->key = key;
            }
        }
        void invalidate() {
            this->head = {};
            this->tail = {};
            this->n = {};
        }
        void deleteList() {
            ListNode* tmp{};
            ListNode* cur{this->head};
            while (cur) {
                tmp = cur->next;
                delete cur;
                cur = tmp;
            }
        }
        LList& _append(ListNode* newNode) {
            this->tail->prev->next = newNode;
            this->tail->prev = newNode;
            ++(this->n);
            return *this;
        }
        LList& _prepend(ListNode* newNode) {
            this->head->next->prev = newNode;
            this->head->next = newNode;
            ++(this->n);
            return *this;
        }
        static void node_swap(ListNode*& m, ListNode*& n) {
            ListNode* tmp = m;
            m = n;
            n = tmp;
        }
};

template<typename U>
std::ostream& operator<<(std::ostream& out, const LList<U>& A) {
    out << '[';
    if (!A.isEmpty()) {
        auto cur = A.head->next;
        for (; cur->next != A.tail; cur = cur->next)
            out << cur->key << ", ";
        out << cur->key;
    }
    out << ']';
    return out;
}

#endif  // __LLIST_H