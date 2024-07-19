#include "array.h"

int main(void)
{
    Array<int> arr;
    for (int i{}; i < 20; i++)
        arr.append(i*i);
    std::cout << "arr : " << arr <<std::endl;
    std::cout << "arr.size() : " << arr.size() << std::endl;
    std::cout << "arr.capacity() : " << arr.capacity() << std::endl;
    std::cout << "\narr[4] : " << arr[14] << std::endl;
    std::cout << "Assigning 24 to arr[14] and swapping values at indices 0 and 5...\n";
    arr[14] = 24;
    arr.swap(0, 5);
    std::cout << "arr : " << arr << std::endl;
    newline;

    Array<std::string> str_arr;
    str_arr.append("This");
    str_arr.append(std::string("is"));
    str_arr.append(std::string("an"));
    str_arr.append("array");
    str_arr.append(std::string("of"));
    str_arr.append(std::string("std::strings"));
    std::cout << "str_arr : " << str_arr << std::endl;
    std::cout << "str_arr[5] : " << str_arr[5] << std::endl;
    newline;

    Array<const char*> cstr_arr;
    cstr_arr.append("This");
    cstr_arr.append("is");
    cstr_arr.append("an");
    cstr_arr.append("array");
    cstr_arr.append("of");
    cstr_arr.append("c_strings");
    std::cout << "cstr_arr : " << cstr_arr << std::endl;
    std::cout << "cstr_arr[3] : " << cstr_arr[3] << std::endl;
    newline;

    double d_arr[] = {2.154, 45.21, 9.7841, 0.469, 3.56};
    Array<double> d_array(d_arr, std::size(d_arr));
    d_array.append(3.14159265);
    std::cout << "d_array : " << d_array << std::endl;
    std::cout << "d_array.size() : " << d_array.size() << std::endl;
    std::cout << "d_array.capacity() : " << d_array.capacity() << std::endl;
    std::cout << "d_array[5] : " << d_array[5] << std::endl;

    return 0;
}