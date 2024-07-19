/*
 * std::begin() and std::end() methods return iterators to the first
 * element and the element after the end of the container respectively.
 * 
 * They are useful when working with arrays which do not have the begin()
 * and end() methods defined as in our custom classes.
 * 
 * In case of arrays std::begin() returns a pointer to the first element
 * of the array and std::end() returns a pointer to the last element of
 * the array.
 * 
 * In case of classes std::begin() returns exactly the begin() method of
 * the class and std::end() method returns exactly the end() method of
 * the class.
 * 
 * This provides us with a unified way of working with arrays as well as
 * custom containers.
 */
#include "iterator.h"

int main(void)
{
    List<int> nums{95, 18, 64, 31, 11, 66, 9};
    List<int>::iterator begin = nums.begin();
    List<int>::iterator end = nums.end();
    for (; begin != end; ++begin)
        std::cout << *begin << ' ';
    std::cout << '\n';

    int arr[] = {21, 15, 64, 12, 98, 1, 3, 47};
    int* begin_a = std::begin(arr);
    int* end_a = std::end(arr);
    for (; begin_a != end_a; ++begin_a)
        std::cout << *begin_a << ' ';
    std::cout << '\n';

    return 0;
}