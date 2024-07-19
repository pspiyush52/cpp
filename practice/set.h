#ifndef __SET_H
#define __SET_H

#include <iostream>
#include <initializer_list>
#include <stack>

template<typename T>
class Set;

template<typename T>
class __tree_iterator;

template<typename T>
class _bintree_node{
    friend class Set<T>;
    friend class __tree_iterator<T>;
    public:
        _bintree_node(const T& item):
            data(item), left(nullptr), right(nullptr){}
    private:
        T data;
        _bintree_node* left;
        _bintree_node* right;
        bool visited;
};

template<typename T>
class Set{
    typedef _bintree_node<T> node;
    friend class __tree_iterator<T>;
    public:
        typedef __tree_iterator<T> iterator;
        Set() = default;
        bool is_empty() const{
            return (root == nullptr);
        }
        Set(std::initializer_list<T> args){
            const T* iter = args.begin();
            for (; iter != args.end(); ++iter)
                this->insert(*iter);
        }
        Set& insert(const T& item){
            node* new_node = new node(item);
            if (!root)
                root = new_node;
            else{
                node* cur = this->root;
                node* parent = this->root;
                while (cur){
                    parent = cur;
                    if (item < cur->data)
                        cur = cur->left;
                    else if (item > cur->data)
                        cur = cur->right;
                    else
                        return *this;
                }
                if (item < parent->data)
                    parent->left = new_node;
                else
                    parent->right = new_node;
            }
            ++size;
            return *this;
        }
        Set& insert(T&& item){
            node* new_node = new node(item);
            if (!root)
                root = new_node;
            else{
                node* cur = this->root;
                node* parent = this->root;
                while (cur){
                    parent = cur;
                    if (item < cur->data)
                        cur = cur->left;
                    else if (item > cur->data)
                        cur = cur->right;
                    else
                        return *this;
                }
                if (item < parent->data)
                    parent->left = new_node;
                else
                    parent->right = new_node;
            }
            ++size;
            return *this;
        }
        bool contains(const T& item) const{
            if (!root)
                return false;
            node* cur = this->root;
            while (cur){
                if (item < cur->data)
                    cur = cur->left;
                else if (item > cur->data)
                    cur = cur->right;
                else
                    return true;
            }
            return false;
        }
        bool contains(T&& item) const{
            if (!root)
                return false;
            node* cur = this->root;
            while (cur){
                if (item < cur->data)
                    cur = cur->left;
                else if (item > cur->data)
                    cur = cur->right;
                else
                    return true;
            }
            return false;
        }
        __tree_iterator<T> begin(){
            return __tree_iterator<T>(this->root);
        }
        __tree_iterator<T> end(){
            return __tree_iterator<T>();
        }
        Set operator+(Set& rhs){
            Set tmp;
            iterator iter = this->begin();
            ++iter;
            for (; iter != this->end(); ++iter)
                tmp.insert(*iter);
            iterator rhs_iter = rhs.begin();
            ++rhs_iter;
            for (; rhs_iter != rhs.end(); ++rhs_iter)
                tmp.insert(*rhs_iter);
            return tmp;
        }
        Set operator-(Set& rhs){
            Set tmp;
            iterator iter = this->begin();
            ++iter;
            for (; iter != this->end(); ++iter){
                if (!rhs.contains(*iter))
                    tmp.insert(*iter);
            }
            return tmp;
        }
        ~Set(){
            this->__tree_delete(this->root);
        }
        template<typename U>
        friend std::ostream& operator<<(std::ostream& output, const Set<U>& B);
        static void __print_tree(node* root){
            if (!root)
                return;
            __print_tree(root->left);
            std::cout << root->data << ' ';
            __print_tree(root->right);
        }

    private:
        node* root{nullptr};
        size_t size{};
        
        static void __tree_delete(node* root){
            if (!root)
                return;
            __tree_delete(root->left);
            __tree_delete(root->right);
            delete root;
            root = nullptr;
        }
        static void __set_unvisited(node* root){
            if (!root)
                return;
            __set_unvisited(root->left);
            __set_unvisited(root->right);
            root->visited = false;
        }
};

template<typename U>
std::ostream& operator<<(std::ostream& output, const Set<U>& B){
    output << "{ ";
    Set<U>::__print_tree(B.root);
    output << '}';
#ifdef __SET_H_DEBUG
    output << ' ' << &B;
#endif
    return output;
}

template<typename T>
class __tree_iterator{
    typedef _bintree_node<T> node;
    public:
        __tree_iterator() = default;
        __tree_iterator(node* root) : stack_ptr(new std::stack<node*>){
            Set<T>::__set_unvisited(root);
            stack_ptr->push(root);
            tree_node = root;
            while(tree_node->left)
                tree_node = tree_node->left;
        }
        __tree_iterator& operator++(){
            if (stack_ptr->empty()){
                delete stack_ptr;
                tree_node = nullptr;
                stack_ptr = nullptr;
                return *this;
            }
            node* cur = stack_ptr->top();
            if (!cur->visited){
                node* tmp = cur->left;
                while (tmp){
                    tmp->visited = true;
                    stack_ptr->push(tmp);
                    tmp = tmp->left;
                }
                cur->visited = true;
            }
            cur = stack_ptr->top();
            stack_ptr->pop();
            if (cur->right)
                stack_ptr->push(cur->right);
            this->tree_node = cur;
            return *this;
        }
        T& operator*() const {
            return tree_node->data;
        }
        bool operator==(const __tree_iterator& rhs) const{
            return (this->tree_node == rhs.tree_node);
        }
        ~__tree_iterator(){
            delete stack_ptr;
            stack_ptr = nullptr;
            tree_node = nullptr;
        }
    private:
        node* tree_node{nullptr};
        std::stack<node*>* stack_ptr{nullptr};
};

#endif  // __SET_H