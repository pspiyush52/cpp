#include "my.h"

/*
 * Syntax:
 * 
 *      [capture list] (parameters) -> return type {
 *          Function body
 *      }
 */

int main(void)
{
    []()
    {
        std::cout << "Lambda function called.\n";
    }(); // ending parantheses to call the lambda function directly

    // assigning a lambda function to a variable
    auto func = [](int& x) {
        x = (++x) * x;
    };
    std::cout << "sizeof(func) : " << sizeof(func) << std::endl;

    int num{4};

    func(num); // the variable can be used as a normal function
    std::cout << "num : " << num << std::endl;
    func(num);
    std::cout << "num : " << num << std::endl;
    nl
    
    // We use capture list to access, or capture, variables from the surrounding scope
    auto fun = [num](){
        std::cout << "inside lambda with num captured by value : " << num << std::endl;
    };
    // here we have captured num by value and so the lambda stores the value of num when
    // it is created and further modifications to num do not affect the copy of the value
    // of num within the lambda

    fun();
    std::cout << "Assigning 12 to num.\n";
    num = 12;
    fun(); // changing num outside does not affect the num inside the lambda function
    std::cout << "Changing num does not affect the copy of num inside the lambda function.\n\n";

    // But if we capture num by reference, then the changes will be reflected inside the
    // lambda as well
    auto ref_fun = [&num] {
        std::cout << "inside lambda with num captured by reference : " << num << std::endl;
    };
    ref_fun();
    std::cout << "Assigning 80 to num.\n";
    num = 80;
    ref_fun(); // the changes made to num will be reflected inside the lambda function
    nl

    int x{};
    int y{1};
    double r{0.679};

    // we can use a capture default mode to indicate how to capture any outside variables
    // that are referenced within the lambda body. Only those variables that are mentioned
    // in the lambda body are captured when a capture-default is used.
    auto cap_fun = [&]() {
        std::cout << "Captured by reference : \nx : " << x << ", y : " << y << ", r : " << r;
        std::cout << ", num : " << num << std::endl;
    }; // here we capture x, y, r and num by reference
    cap_fun();
    r = 1.74845;
    x = 100;
    cap_fun(); // changes will be reflected inside the lambda
    nl

    // using [=] will capture any mentioned variables in the body of the lambda function by
    // value.
    auto val_fun = [=]() {
        std::cout << "Captured by value : \nx : " << x << ", y : " << y << ", r : " << r << std::endl;
    }; // here we capture x, y and r by value
    val_fun();
    x = 0;
    y = -11;
    r = 8.3015547;
    val_fun(); // values captured in the lambda will not be modified
    nl

    // if we want all the mentioned variables to be captured by reference except for num, we can use the
    // following syntax
    auto num_val = [&, num]() {
        std::cout << "x : " << x << ", y : " << y << ", num : " << num << std::endl;
        // num++; // variables captured by value cannot be modified inside the lambda function
    }; // here we capture x and y by reference and num by value
    num_val();
    x = y = 10;
    num = 40;
    num_val(); // changes will be reflected in x and y but not in num
    nl

    auto lambda = [&]() {
        std::cout << "num : " << num << std::endl;
        num *= 10; // variables captured by reference can be modified inside the lambda function
    };
    lambda();
    lambda();

    return 0;
}