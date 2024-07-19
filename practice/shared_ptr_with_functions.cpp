#include "utils.h"

template<typename T> void show(const s_ptr<T>& ptr);
s_ptr<int> get_int(int num);

/*
    Shared pointers should never be returned by reference as the reference
    count does not go up.
    When the makes() function is called it creates a shared pointer to shared
    pointer to obj and it returns the SP to obj but when the function returns,
    the SP to SP to obj goes out of scope and so the memory its pointing to is
    released and that means the SP to obj is released and which in turn means
    the new object obj is released from memory and when the function returns
    there is no object left in memory.
*/
template<typename T>
s_ptr<T>& makes(const T& obj){
    s_ptr<s_ptr<T>> ptr = make_s<s_ptr<T>>(make_s<T>(obj));
    return *ptr;
}

int main(void)
{
    s_ptr<int> iptr = get_int(245);
    /*
        Even if the get_int() function is returning a shared_ptr by value, the
        use_count of the SP will remain 1 as the compiler does some internal
        optimizations to make it so that the function does not return by value
        but by reference and no copies are made unlike the usual return by
        value.
    */
    show(iptr);
    s_ptr<int> iptr2 = iptr;
    // Now the use_count will increment
    show(iptr);
    sep;

    std::cout << "*iptr2 : " << *iptr2 << '\n';
    show(iptr2);
    iptr2.reset(new int{23});
    std::cout << "*iptr2 : " << *iptr2 << '\n';
    show(iptr2);
    sep;

    s_ptr<int>& ptr = makes<int>(13);
    // Using ptr will cause a seg fault because the SP is already deleted from
    // memory when the function makes() returns
    // std::cout << "ptr.use_count() : " << ptr.use_count() << '\n';

    return 0;
}

s_ptr<int> get_int(int num){
    s_ptr<int> ptr {new int{num}};
    return ptr;
}

template<typename T>
void show(const s_ptr<T>& ptr){
    std::cout << "use_count : " << ptr.use_count() << '\n';
}