#ifndef __AVL_MAP_H
#define __AVL_MAP_H

#include "functors.h"

template<typename key_tp, typename value_tp>
class Map;

template<typename key_tp, typename value_tp>
class __map_node{
    public:
    friend class Map<key_tp, value_tp>;
    key_tp __key{};
    value_tp __value{};
    __map_node* __left{};
    __map_node* __right{};
    int __height{};
    public:
        __map_node(const key_tp& key, const value_tp& value) : __key(key), __value(value){}
};

template<typename key_tp, typename value_tp>
class Map{
    typedef __map_node<key_tp, value_tp> node;
    public:
        typedef                   key_tp           key_type;
        typedef                 value_tp           value_type;
        typedef                  key_tp&           kref;
        typedef            const key_tp&           const_kref;
        typedef                value_tp&           vref;
        typedef          const value_tp&           const_vref;
    
    public:
        Map() = default;
        bool is_empty() const{ return (this->__root == nullptr); }
        size_t size() const { return this->__size; }
        const_vref min() const{
            if (this->is_empty())
                throw 0;
            node* parent = this->__root;
            node* left = parent->__left;
            for (; left; parent = left, left = parent->__left);
            return (parent->__value);
        }
        const_vref max() const{
            if (this->is_empty())
                throw 0;
            node* parent = this->__root;
            node* right = parent->__right;
            for (; right; parent = right, right = parent->__right);
            return (parent->__value);
        }
        bool in(const_kref key) const{
            return __search__(this->__root, key);
        }
        vref operator[](const_kref key){
            node* parent{};
            node* res = __search__(this->__root, parent, key);
            if (!res){
                node* new_node = new node(key, {});
                if (parent){
                    if (key < parent->__key)
                        parent->__left = new_node;
                    else
                        parent->__right = new_node;
                }
                else{
                    // this->__root = 
                }
                ++this->__size;
                res = new_node;
            }
            return res->__value;
        }
        ~Map(){
            __release__(this->__root);
            this->__root = {};
        }
        friend std::ostream& operator<<(std::ostream& output, const Map& s){
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
        node* __ins__(const_kref key, vref value){
            bool inserted = true;
            node* new_node = new node(key, value);
            node* tmp =__insert__(this->__root, new_node, inserted);
            if (inserted){
                this->__root = tmp;
                ++this->__size;
            }
            else
                delete new_node;
        }
        static node* __insert__(node* root, node* n, bool& flag){
            if (!root)
                return n;
            if (n->__key == root->__key){
                flag = false;
                return root;
            }
            else if (n->__key < root->__key)
                root->__left = __insert__(root->__left, n, flag);
            else
                root->__right = __insert__(root->__right, n, flag);
            
            if (flag){
                __update__(root);
                int k = __balance__(root);
                if (k > 1){
                    if (n->__key > root->__right->__key)
                        return __rotate_left__(root);
                    else{
                        root->__right = __rotate_right__(root->__right);
                        return __rotate_left__(root);
                    }
                }
                if (k < -1){
                    if (n->__key < root->__left->__key)
                        return __rotate_right__(root);
                    else{
                        root->__left = __rotate_left__(root->__left);
                        return __rotate_right__(root);
                    }
                }
            }
            return root;
        }
        static node* __search__(node* root, node*& parent, const_kref key){
            if (!root)
                return {};
            node* cur = root;
            while (cur){
                if (key == cur->__key)
                    return cur;
                else if (key < cur->__key)
                    cur = cur->__left;
                else
                    cur = cur->__right;
                parent = cur;
            }
            return {};
        }
        static void __inorder__(std::ostream& output, node* root){
            if (!root)
                return;
            __inorder__(output, root->__left);
            output << '(' << root->__key << " : " << root->__value << ')';
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

#endif  // __AVL_MAP_H