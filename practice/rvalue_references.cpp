/*
 * When an rvalue reference is bound to an rvalue, the life of the rvalue
 * is extended, and we can manipulate it through the reference.
 * 
 * When an rvalue expression is assigned to an lvalue first the
 * expression is evaluated and the result is stored in a temporary memory
 * location and then the result is copied from the temporary memory
 * location to the lvalue and the temporary memory is destroyed.
 * Ex:
 *              int x{5};
 *              int y{12};
 *              auto result = x + y;
 * x + y is an rvalue expression so the result of the addition will be
 * stored in a temporary memory location and then copied to the result
 * lvalue.
 * 
 * We can bypass this unnecessary copying and extend the life of the
 * temporary memory location by binding it to an rvalue reference so that
 * we can refer to it directly later in the code using the rvalue
 * reference. This eliminates the unnecessary copying.
 *              int&& result = x + y;
 * now result is an rvalue reference which will directly refer to the
 * temporary memory location where the result of the rvalue expression 
 * (x + y) is stored.
 */
#include <iostream>
#include "arr_string.h"

double add(double a, double b){ return a + b; }

void fun(const string& s){
	std::cout << "fun(const string&) called\n";
}

void fun(string&& s){
	std::cout << "fun(string&&) called\n";
}

int main(void)
{
    int x{5}, y{12};
    int&& result = x + y;
    std::cout << "result: " << result << '\n';

    /*
     * const lvalue references can also be bound to rvalues but then they
     * cannot be used to modify  the rvalue. So if we need to modify the
     * rvalue we should use non-const rvalue references as are used in
     * move constructors:    ClassName(ClassName&& src),
     * the parameter is an rvalue reference.
     */

    // Since add is returning by value, it returns and rvalue which can
    // be copied to a variable and used later but we can avoid the copy
    // by directly referencing the rvalue using the && syntax.
    auto&& sum = add(12.14, 65.483);
    std::cout << "sum: " << sum << '\n';

    string name{"Niharika"};
	
	// Casting lvalue to rvalue reference will result in the function
	// with rvalue reference parameter being called
	fun(std::move(name));
	std::cout << "name: " << name << '\n';

	// Results in a temporary string object being created so the function
	// with rvalue reference parameter is called
	fun("Piyush");

    return 0;
}