#include <iostream>
#include <initializer_list>
#include <concepts>
#include <string.h>

template<typename T>
concept stream_insertible = requires (std::ostream& output, T obj){
    output << obj;
};

template<typename T>
class Array{
    public:
        explicit Array(size_t size = 16) : arr(new T[size]), arr_size(size){}
        Array(std::initializer_list<T> args){
            size_t args_size = args.size();
            arr = new T[args_size];
            arr_size = args_size;
            memcpy(arr, args.begin(), sizeof(T) * args_size);
        }
        
        template<typename U>
        requires stream_insertible<U>  // Must be a stream insertible type
        friend std::ostream& operator<<(std::ostream& output, const Array<U>& A);

        ~Array(){ delete[] arr; arr_size = 0; }
    
    private:
        T* arr;
        size_t arr_size;
};

template<typename T>
requires stream_insertible<T>
std::ostream& operator<<(std::ostream& output, const Array<T>& A)
{
    if (A.arr_size == 0)
        output << "[]";
    else
    {
        size_t i{}, upto{A.arr_size - 1};
        output << '[';
        for (; i < upto; i++)
            output << A.arr[i] << ", ";
        output << A.arr[i] << ']';
    }
    return output;
}

class Point{
    public:
        explicit Point() = default;
        Point(double x, double y) : _x(x), _y(y){}
        /*void stream_insert(std::ostream& output) const override{
            output << "Point(x: " << _x << ", y: " << _y << ')';
        }*/
    
    private:
        double _x{};
        double _y{};
};

int main(void)
{
    Array<int> nums{4, 94, 12, 67, 32, 19, 61, 3, 41};
    std::cout << "Array of integers: " << nums << '\n';  // works

    Array<Point> parr(3);

    // Will work only if Point objects are stream insertable
    // std::cout << "Array of points: " << parr << '\n';

    return 0;
}