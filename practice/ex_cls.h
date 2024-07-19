#ifndef __EX_CLS_H
#define __EX_CLS_H

#include "arr_strings.h"

class MyExcept{
    public:
        MyExcept(const char* str) : message(str){
            std::cout << "MyExcept object constructed at " << this << '\n';
        }
        MyExcept(const MyExcept& src){
            std::cout << "Copied MyExcept object from " << &src << " to " << this << '\n';
            message = src.message;
        }
        MyExcept(MyExcept&& src) : message(std::move(src.message)){
            std::cout << "MyExcept object moved from " << &src << " to " << this << '\n';
        }
        ~MyExcept(){ std::cout << "MyExcept object at " << this << " destroyed\n"; }
        const string& what() const { return message; }
    private:
        string message;
};

#endif  // __EX_CLS_H