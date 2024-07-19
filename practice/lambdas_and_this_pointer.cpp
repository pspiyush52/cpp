/*
 * If we have a lambda function inside any member function of a class and
 * we try to access any other members of the class from inside the lambda
 * we will get a compiler error since the lambda function by default does
 * not have access to the this pointer of the enclosing class.
 * If we want to access members of the class then we can capture the this
 * pointer inside the lambda.
 */
#include <iostream>

class MyClass{
    public:
        MyClass() = default;
        MyClass(int num) : data(num){}
        void fun(){
            std::cout << "Inside fun() method..., data = " << data++ << '\n';
            [this](){
                // The data member variable can be accessed only after
                // capturing the this pointer in the lambda function
                std::cout << "Inside lambda function..., data = "
                    << data++ << "\n\n";
            }();
        }
    private:
        int data{};
};

int main(void)
{
    MyClass obj;
    obj.fun();
    obj.fun();
    obj.fun();
    return 0;
}