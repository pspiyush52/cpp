#include <iostream>
#include <cstdio>
#include <string_view>
#define newline printf("\n");

template<typename T>
class Array {
    public:
        Array(size_t Size = 16);
        void append(T item);
        T& operator[](size_t i);
        ~Array();
    private:
        T* arr;
        size_t top;
        size_t size;
        bool is_full();
        bool is_empty();
        template<typename U> friend std::ostream& operator<<(std::ostream& output, Array<U>& arr);
};

template<typename T> Array<T>::Array(size_t Size)
{
    arr = new T[Size];
    top = 0;
    size = Size;
}

template<typename T> bool Array<T>::is_full()
{
    return (top == size);
}

template<typename T> bool Array<T>::is_empty()
{
    return (top == 0);
}

template<typename T> void Array<T>::append(T item)
{
    if (is_full())
    {
        std::cerr << "ERROR: Array full.\n";
        return;
    }
    arr[top++] = item;
}

template<typename T>
T& Array<T>::operator[](size_t i)
{
    if (i > (top - 1))
    {
        std::cerr << "ERROR: Array index out of bounds.\n";
        (*this).~Array();
        exit(1);
    }
    return arr[i];
}

template<typename T> Array<T>::~Array()
{
    delete[] arr;
    top = -1;
    size = 0;
}

template<typename T>
std::ostream& operator<<(std::ostream& output, Array<T>& A)
{
    if (A.is_empty())
        output << "[]";
    else
    {
        size_t i{};
        output << "[";
        for (; i < A.top - 1; i++)
            output << A.arr[i] << ", ";
        output << A.arr[i] << "]";
    }
    return output;
}

template<>
std::ostream& operator<< <std::string_view> (std::ostream& output, Array<std::string_view>& A)
{
    if (A.is_empty())
        output << "[]";
    else
    {
        size_t i{};
        output << "[";
        for (; i < A.top - 1; i++)
            output << "\"" << A.arr[i] << "\", ";
        output << "\"" << A.arr[i] << "\"]";
    }
    return output;
}

template<>
std::ostream& operator<< <const char*> (std::ostream& output, Array<const char*>& A)
{
    if (A.is_empty())
        output << "[]";
    else
    {
        size_t i{};
        output << "[";
        for (; i < A.top - 1; i++)
            output << "\"" << A.arr[i] << "\", ";
        output << "\"" << A.arr[i] << "\"]";
    }
    return output;
}

template<typename T> void print_arr(T arr[], size_t size);

int main(void)
{
    int iarr[] = {8, 7, 1, 10, 32, 65, 4, 15, 17, 63};
    std::cout << "int array : ";
    print_arr(iarr, std::size(iarr));
    newline

    double darr[] = {1.45, 3.19, 5.124, 0.707, 10.8974, 22.54, 3.414, 2.208, 3.021, 4.98012, 6.76139};
    std::cout << "double array : ";
    print_arr(darr, std::size(darr));
    newline

    char carr[] {"Character array"};
    std::cout << "character array : ";
    print_arr(carr, std::size(carr) - 1);
    newline

    newline
    Array<int> arr(16);
    for (int i{}; i < 10; i++)
        arr.append(i*i);
    std::cout << "arr : " << arr << std::endl;

    Array<char> charr(20);
    for (char i{}; i < 15; i++)
        charr.append('a' + i);
    std::cout << "charr : " << charr << std::endl;

    Array<double> double_arr(10);
    for (int i{}; i < 12; i++)
        double_arr.append(darr[i]);
    std::cout << "double_arr : " << double_arr << std::endl;

    std::cout << "arr[3] : " << arr[3] << std::endl;
    arr[3] = 45;
    std::cout << "arr[3] : " << arr[3] << std::endl;
    arr[9] = 0;
    std::cout << "arr : " << arr << std::endl;
    newline

    Array<std::string_view> sv_arr(10);
    sv_arr.append("This");
    sv_arr.append("is");
    sv_arr.append("a");
    sv_arr.append("sample");
    sv_arr.append("array");
    sv_arr.append("of");
    sv_arr.append("strings");
    std::cout << "sv_arr : " << sv_arr << std::endl;
    std::cout << "sv_arr[4] : " << sv_arr[4] << std::endl;
    newline

    Array<const char*> cc_arr(10);
    cc_arr.append("This");
    cc_arr.append("is");
    cc_arr.append("a");
    cc_arr.append("sample");
    cc_arr.append("array");
    cc_arr.append("of");
    cc_arr.append("strings");
    std::cout << "cc_arr : " << cc_arr << std::endl;
    std::cout << "cc_arr[6] : " << cc_arr[6] << std::endl;

    return 0;
}

template<typename T>
void print_arr(T arr[], size_t size)
{
    size_t i{};
    size--;
    std::cout << "[";
    for (; i < size; i++)
        std::cout << arr[i] << ", ";
    std::cout << arr[i] << "]";
}