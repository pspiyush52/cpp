/*
 * Class template std::function is a general purpose polymorphic function
 * wrapper. Instances of std::function can store, copy and invoke any
 * CopyConstructible Callable target --
 *          1. Functions (via pointers thereto)
 *          2. Lambda expressions
 *          3. Bind expressions or other function objects as well as
 * pointers to member functions and pointers to data members.
 * 
 * The stored callable object is called the target of std::function. If a
 * std::function contains no target, it is called empty. Invoking the
 * target of an empty std::function results in a std::bad_function_call
 * exception being thrown.
 * 
 * The basic usage of std::function is to provide the flexibility of
 * using either function pointers or functors or lambda functions as
 * callbacks in higher order functions.
 */
#include <iostream>
#include <functional>

template<typename T>
void print_num(T num){
    std::cout << "Num(function): " << num << '\n';
}

struct Printer{
    void operator()(double num){
        std::cout << "Num(functor): " << num << '\n';
    }
};

template<typename T>
std::function<void(T)> some_fun = print_num<T>;

int main(void)
{
    double x{12.4792};
    
    // Creating an instance of std::function which wraps around a
    // function returning void which takes an integer as a parameter
    std::function<void(double)> print_fun = print_num<double>;
    
    // Using the std::function instance to invoke the target of the
    // std::function
    print_fun(x);

    // We can use the std::function instance to store a different type of
    // callable this time(a lambda function) with the same params and
    // return type
    print_fun = [](double num){
        std::cout << "Num(lambda): " << num << '\n';
    };

    print_fun(x);

    Printer printer_obj;
    // Storing a functor in the std::function instance
    print_fun = printer_obj;

    print_fun(x);
    
    // Using templated std::function instance
    some_fun<double>(x);

    return 0;
}