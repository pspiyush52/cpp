#ifndef __AVL_H
#define __AVL_H

#include <iostream>
#include "functors.h"

template<typename T, typename Projection = identity>
class Set;

template<typename T, typename Projection>
class __set_node{
    friend class Set<T, Projection>;
    T __item{};
    __set_node* __left{};
    __set_node* __right{};
    int __height{};
    public:
        template<typename... Arguments>
        __set_node(Arguments... args) : __item(args...){}
};

template<typename T, typename Projection>
class Set{
    typedef __set_node<T, Projection> node;
    public:
        typedef            T        value_type;
        typedef            T*       pointer;
        typedef      const T*       const_pointer;
        typedef            T&       reference;
        typedef      const T&       const_reference;
        Set() = default;
        Set(std::initializer_list<T> args){
            auto iter = args.begin();
            for (; iter != args.end(); ++iter)
                this->insert(*iter);
        }
        bool is_empty() const{ return (this->__root == nullptr); }
        template<typename... Arguments>
        Set& insert(Arguments... args){
            node* new_node = new node(args...);
            bool inserted = true;
            node* tmp = __insert__(this->__root, new_node, inserted);
            if (inserted){
                this->__root = tmp;
                ++this->__size;
            }
            else
                delete new_node;
            return *this;
        }
        Set& insert(T* ptr){
            bool inserted = true;
            node* tmp = __insert__(this->__root, ptr, inserted);
            if (inserted){
                this->__root = tmp;
                ++this->__size;
            }
            return *this;
        }
        size_t size() const { return this->__size; }
        // int height() const{ return this->__root->__height; }
        const_reference min() const{
            if (this->is_empty())
                throw 0;
            node* parent = this->__root;
            node* left = parent->__left;
            for (; left; parent = left, left = parent->__left);
            return (parent->__item);
        }
        const_reference max() const{
            if (this->is_empty())
                throw 0;
            node* parent = this->__root;
            node* right = parent->__right;
            for (; right; parent = right, right = parent->__right);
            return (parent->__item);
        }
        bool in(const_reference key) const{
            return __search__(this->__root, key);
        }
        reference search(const_reference key){
            node* res = __search__(this->__root, key);
            return res->__item;
        }
        const_reference search(const_reference key) const{
            node* res = __search__(this->__root, key);
            return res->__item;
        }
        ~Set(){
            __release__(this->__root);
            this->__root = {};
        }
        friend std::ostream& operator<<(std::ostream& output, const Set& s){
            output.put('{');
            if (!s.is_empty()){
                output.put(' ');
                s.__inorder__(output, s.__root);
            }
            output.put('}');
            return output;
        }
    private:
        node* __root{};
        size_t __size{};
        inline static Projection proj{};

        static int __height__(node* n){ return (n) ? n->__height : -1; }
        static int __balance__(node* root){
            return __height__(root->__right) - __height__(root->__left);
        }
        static void __update__(node*& root){
            root->__height = ::max(__height__(root->__left), __height__(root->__right)) + 1;
        }
        static node* __rotate_left__(node* root){
            node* tmp = root->__right->__left;
            node* new_root = root->__right;
            root->__right->__left = root;
            root->__right = tmp;
            __update__(root);
            __update__(new_root);
            return new_root;
        }
        static node* __rotate_right__(node* root){
            node* tmp = root->__left->__right;
            node* new_root = root->__left;
            root->__left->__right = root;
            root->__left = tmp;
            __update__(root);
            __update__(new_root);
            return new_root;
        }
        node* __ins__(node* new_node){
            bool inserted = true;
            return __insert__(this->__root, new_node, inserted);
        }
        static node* __insert__(node* root, node* n, bool& flag){
            if (!root)
                return n;
            if (proj((root->__item)) == proj((n->__item))){
                flag = false;
                return root;
            }
            else if (proj((n->__item)) < proj((root->__item)))
                root->__left = __insert__(root->__left, n, flag);
            else
                root->__right = __insert__(root->__right, n, flag);
            
            if (flag){
                root->__height = ::max(__height__(root->__left), __height__(root->__right)) + 1;
                int k = __balance__(root);
                
                if (k > 1){
                    if (proj((root->__right->__item)) < proj((n->__item)))
                        return __rotate_left__(root);
                    else{
                        root->__right = __rotate_right__(root->__right);
                        return __rotate_left__(root);
                    }
                }
                else if (k < -1){
                    if (proj((n->__item)) < proj((root->__left->__item)))
                        return __rotate_right__(root);
                    else{
                        root->__left = __rotate_left__(root->__left);
                        return __rotate_right__(root);
                    }
                }
            }
            return root;
        }
        static node* __search__(node* root, const_reference key){
            if (!root)
                return {};
            node* cur = root;
            while (cur){
                if (key == cur->__item)
                    return cur;
                else if (proj(key) < proj(cur->__item))
                    cur = cur->__left;
                else
                    cur = cur->__right;
            }
            return {};
        }
        static void __preorder__(node* root){
            if (!root)
                return;
            std::cout << ((root->__item)) << ' ';
            __preorder__(root->__left);
            __preorder__(root->__right);
        }
        static void __inorder__(std::ostream& output, node* root){
            if (!root)
                return;
            __inorder__(output, root->__left);
            output << ((root->__item)) << ' ';
            // output << "key: " << (*(root->__item)) << ", h: " << root->__height << " | ";
            __inorder__(output, root->__right);
        }
        static void __release__(node* root){
            if (!root)
                return;
            __release__(root->__left);
            __release__(root->__right);
            delete root;
        }
};

#endif  // __AVL_H