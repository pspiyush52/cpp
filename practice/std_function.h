#ifndef __STD_FUNCTION_H
#define __STD_FUNCTION_H

#include <iostream>
#include <functional>

std::ostream& operator<<(std::ostream& output, std::function<void(int)> fun){
    output << "<std::function object at " << &fun << '>';
    return output;
}

void printer_fun(int num){
    std::cout << "Num(function): " << num << '\n';
}

struct Printer{
    void operator()(int num){
        std::cout << "Num(functor): " << num << '\n';
    }
};

auto printer_lambda = [](int num){
    std::cout << "Num(lambda): " << num << '\n';
};

#endif  // __STD_FUNCTION_H