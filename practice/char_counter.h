#ifndef __CHAR_COUNTER_H
#define __CHAR_COUNTER_H

#include <iostream>
#include <ctype.h>
#include <stdlib.h>

struct cnode{
    cnode(char ch) : __ch(ch){}
    char __ch;
    int __count{1};
    cnode* left{};
    cnode* right{};
};

class Counter{
    public:
        Counter() = default;
        Counter(const char* str){
            if (str)
                for (; *str; ++str)
                    this->insert(*str);
        }
        Counter& insert(char ch){
            if (__insert__(this->__root, ch))
                ++this->__size;
            return *this;
        }
        size_t size() const{ return this->__size; }
        ~Counter(){
            __release__(this->__root);
            this->__root = nullptr;
        }
        friend std::ostream& operator<<(std::ostream& output, const Counter& c){
            if (c.__root == nullptr)
                output << "{}";
            else{
                output << "{ ";
                c.__print__(output, c.__root);
                output.put('}');
            }
            return output;
        }
    private:
        cnode* __root{};
        size_t __size{};
        static bool __insert__(cnode*& root, char ch){
            if (!root){
                root = new cnode(ch);
                return true;
            }
            if (root->__ch > ch)
                return __insert__(root->left, ch);
            else if (root->__ch < ch)
                return __insert__(root->right, ch);
            else
                ++root->__count;
            return false;
        }
        static void __release__(cnode*& root){
            if (!root)
                return;
            __release__(root->left);
            __release__(root->right);
            delete root;
        }
        static void __print__(std::ostream& output, cnode* root){
            if (!root)
                return;
            __print__(output, root->left);
            output << "('";
            output << (root->__ch);
            output << "':";
            output << (root->__count);
            output << ") ";
            __print__(output, root->right);
        }
};

#endif  // __CHAR_COUNTER_H