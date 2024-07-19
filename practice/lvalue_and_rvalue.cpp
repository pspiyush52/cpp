/*
 * We know that expressions can evaluate to objects or functions.
 * To help determine how expressions should evaluate and where they can
 * be used, all expressions in C++ have two properties: a Type and a
 * Value category.
 * 
 * The type of an expression is the type of the value, object, or
 * function that results on evaluating the expression, e.g.,
 *          {12 / 4} -> (int / int) => int
 * 
 * The Value category of an expression indicates whether the expression
 * resolves to a value, a function, or an object of some kind.
 * 
 * An entity such as an object or a function that has an 'identity' i.e.,
 * is identifiable can be differentiated from other similar entities
 * (typically by comparing the addresses of the entity).
 * 
 * Any entity with an identity can be accessed via an identifier,
 * reference or a pointer.
 * 
 * An lvalue is an expression that evaluates to an identifiable object or
 * function.
 * 
 * rvalue is an expression that is not an lvalue. rvalues aren't
 * identifiable (as a side effect, they have to be used immediately as
 * they cannot be referred to later on using any identifier, reference or
 * pointer).
 * 
 * Generally speaking, lvalues exist in memory and they can be referenced
 * later using identifiers, references or pointers but rvalues cannot.
 * 
 * Sometimes rvalues are temporary and are quickly destroyed by the
 * system when no longer needed.
 * 
 * We cannot get the address of an rvalue expression using the '&'
 * operator.
 */
#include <iostream>

void fun(int&& num){
    std::cout << "fun(int&&) called with " << num << '\n';
}
void fun(const int& num){
    std::cout << "fun(const int&) called with " << num << '\n';
}

int main(void)
{
    int x = 5;
    fun(2.8);  // generates a temp object in memory so fun(int&&) will be called
    fun(x);
    fun(x + 2);  // generates a temp object in memory so fun(int&&) will be called
    
    return 0;
}