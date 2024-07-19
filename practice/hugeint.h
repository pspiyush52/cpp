#ifndef __HUGEINT_H
#define __HUGEINT_H

#include <iostream>
#include <concepts>
#include <string>

struct __list_node{
    using value_type = int;
    value_type __data;
    __list_node* __next;
    __list_node(value_type data) : __data(data), __next(nullptr){}
};

class h_int{
    using node = __list_node;
    public:
        h_int() = default;
        template<std::integral T>
        h_int (const T& num){
            T rem, __num = num;
            while (__num){
                rem = __num % 10;
                __append_list__(rem);
                __num /= 10;
            }
        }
        h_int (const char* numstr){
            for (; *numstr == '0'; ++numstr);
            if (*numstr == '\0')
                --numstr;
            const char* ptr = numstr;
            while (*ptr++ != '\0');
            ptr -= 2;
            for (; ptr != numstr; --ptr)
                this->__append_list__(static_cast<node::value_type>(*ptr - 48));
            this->__append_list__(static_cast<node::value_type>(*ptr - 48));
        }
        h_int (const h_int& src){
            if (this == &src)
                return;
            node* tmp = src.head;
            this->__clear__();
            __copy__(&(this->head), &(src.head));
        }
        h_int (h_int&& src){
            this->head = src.head;
            src.head = nullptr;
        }
        h_int& operator=(const h_int& src){
            if (this == &src)
                return *this;
            node* tmp = src.head;
            this->__clear__();
            __copy__(&(this->head), &(src.head));
            return *this;
        }
        h_int& operator=(h_int&& src) = delete;
        ~h_int(){
            if (head != nullptr){
                node* tmp = head;
                while (head){
                    tmp = head->__next;
                    delete head;
                    head = tmp;
                }
                head = nullptr;
            }
        }
        friend std::ostream& operator<<(std::ostream& output, const h_int& num);
        friend std::istream& operator>>(std::istream& input, h_int& num);
        friend h_int operator+(const h_int& lhs, const h_int& rhs);
        template<std::integral T>
        friend h_int operator+(const T& lhs, const h_int& rhs);
        template<std::integral T>
        friend h_int operator+(const h_int& lhs, const T& rhs);
        /*friend h_int operator*(const h_int& lhs, const h_int& rhs){
            h_int __lhs{lhs}, __rhs{rhs};
            h_int::__make_equal__(__lhs, __rhs);
        }*/
        friend h_int operator*(const int& lhs, const h_int& rhs){
            node* res_head = h_int::__multiplier__(lhs, rhs.head);
            h_int res;
            res.head = res_head;
            return res;
        }
        friend h_int operator*(const h_int& lhs, const int& rhs){
            return (rhs * lhs);
        }
    
    private:
        node* head{nullptr};
        
        void __append_list__(node::value_type data){
            if (head == nullptr)
                head = new node(data);
            else{
                node* new_node = new node(data);
                new_node->__next = head;
                head = new_node;
            }
        }
        
        void __clear__(){
            if (head == nullptr)
                return;
            node* tmp;
            while (head){
                tmp = head->__next;
                delete head;
                head = tmp;
            }
            head = nullptr;
        }
        
        static void __make_equal__(h_int& lhs, h_int& rhs){
            node* lhead = lhs.head;
            node* rhead = rhs.head;
            while (lhead && rhead){
                lhead = lhead->__next;
                rhead = rhead->__next;
            }
            if (!lhead)
                for (; rhead; rhead = rhead->__next)
                    lhs.__append_list__(0);
            else
                for (; lhead; lhead = lhead->__next)
                    rhs.__append_list__(0);
        }
        
        static node* __adder__(node* lhs, node* rhs){
            if ((lhs->__next == nullptr) && (rhs->__next == nullptr))
                return (new node(lhs->__data + rhs->__data));
            else{
                node* res = __adder__(lhs->__next, rhs->__next);
                node* tmp = new node(lhs->__data + rhs->__data + res->__data / 10);
                if (res->__data > 9)
                    res->__data -= 10;
                tmp->__next = res;
                return tmp;
            }
        }
        
        static node* __add__(node* lhs, node* rhs){
            node* res = __adder__(lhs, rhs);
            if (res->__data > 9){
                node* head = new node(res->__data / 10);
                res->__data -= 10;
                head->__next = res;
                return head;
            }
            return res;
        }

        static node* __multiplier__(const int& lhs, node* rhs){
            if (rhs->__next == nullptr)
                return (new node(lhs * rhs->__data));
            else{
                node* res = __multiplier__(lhs, rhs->__next);
                node* tmp = new node(rhs->__data + res->__data / 10);
                if (res->__data > 9)
                    res->__data %= 10;
                tmp->__next = res;
                return tmp;
            }
        }

        static node* __multiply__(node* lhs, node* rhs){
            if (rhs->__next == nullptr)
                return __multiplier__(rhs->__data, lhs);
            else{
                node* res = __multiply__(lhs, rhs);
                node* tmp = __adder__(lhs, res);
            }
        }
        
        static node* __reverse__(node* head){
            if (head->__next == nullptr)
                return head;
            node* tmp = __reverse__(head->__next);
            head->__next->__next = head;
            head->__next = nullptr;
            return tmp;
        }
        
        static void __copy__(node** dest, node* const* src){
            if ((*src)->__next == nullptr){
                *dest = new node((*src)->__data);
                return;
            }
            __copy__(dest, &(*src)->__next);
            node* new_node = new node((*src)->__data);
            new_node->__next = *dest;
            *dest = new_node;
        }
};

std::ostream& operator<<(std::ostream& output, const h_int& num){
    if (num.head != nullptr){
        for (__list_node* tmp = num.head; tmp; tmp = tmp->__next)
            output << tmp->__data;
    }
    return output;
}

// std::istream& operator>>(std::istream& input, h_int& num){
//     std::string snum;
//     input >> snum;
//     num = h_int{snum.c_str()};
//     return input;
// }

h_int operator+(const h_int& lhs, const h_int& rhs){
    h_int __lhs{lhs}, __rhs{rhs};
    h_int::__make_equal__(__lhs, __rhs);
    h_int::node* res_head = h_int::__add__(__lhs.head, __rhs.head);
    h_int res;
    res.head = res_head;
    return res;
}

template<std::integral T>
h_int operator+(const T& lhs, const h_int& rhs){
    return (h_int(lhs) + rhs);
}

template<std::integral T>
h_int operator+(const h_int& lhs, const T& rhs){
    return (lhs + h_int(rhs));
}

#endif  // __HUGEINT_H