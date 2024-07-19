#include <iostream>
#include <concepts>
#include <limits>
#include "range.h"
#define SHOW_NULL
#define SIZE 4

template<std::integral T>
class table{
    static constexpr double max_load = 0.75;
    public:
        table() : __arr(new T[SIZE]), __size(SIZE), __count(0){
            this->__set__(this->__arr, this->__size, this->null);
        }
        table& insert(const T item){
            if (this->__load__() >= max_load)
                this->__expand__();
            size_t pos = this->__hash_fun__(item);
            if (__not_empty__(pos))
                for (size_t i{1}; __not_empty__(pos); pos = (pos + i*i) % this->__size, ++i);
            this->__arr[pos] = item;
            ++this->__count;
            return *this;
        }
        ~table(){
            delete[] this->__arr;
            this->__arr = nullptr;
        }
        
        friend std::ostream& operator<<(std::ostream& output, const table& t){
            t.__print__(output);
            return output;
        }
    
    private:
        T* __arr;
        size_t __size;
        size_t __count;
        static inline T null{std::numeric_limits<T>::max()};

        static void __set__(T* arr, size_t size, T value){
            T* end = arr + size;
            for (; arr != end; ++arr)
                *arr = value;
        }
        size_t __hash_fun__(const T item){
            return (item % this->__size);
        }
        bool __is_empty__(size_t pos){
            return (this->__arr[pos] == null);
        }
        bool __not_empty__(size_t pos){
            return (this->__arr[pos] != null);
        }
        double __load__(){
            return (1.0 * this->__count / this->__size);
        }
        void __expand__(){
            T* cur_arr{this->__arr};
            size_t cur_size{this->__size};
            this->__size *= 2;
            T* tmp = new T[this->__size];
            this->__set__(tmp, this->__size, this->null);
            this->__rehash__(tmp, cur_size);
            delete[] this->__arr;
            this->__arr = tmp;
        }
        void __rehash__(T* __new, size_t __count_size){
            T item{};
            for (size_t i{}, pos{}; i < __count_size; ++i){
                if ((item = this->__arr[i]) != null){
                    pos = this->__hash_fun__(item);
                    if (__new[pos] != null)
                        for (size_t j{1}; __new[pos] != null; pos = (pos + j*j) % this->__size);
                    __new[pos] = item;
                }
            }
        }
        void __print__(std::ostream& output) const {
            output << '{';
            T* iter = this->__arr;
            T* end = iter + this->__size;
            if (*iter != null)
                output << *iter;
#ifdef SHOW_NULL
            else
                output << "null";
            ++iter;
#endif
            for (; iter != end; ++iter)
                if (*iter != null)
                    output << ", " << *iter;
#ifdef SHOW_NULL
                else
                    output << ", null";
#endif
            output << '}';
        }
};

int main(void)
{
    table<size_t> nums;
    std::cout << nums << '\n';

    for (int n : {1, 34, 2238, 47})
        nums.insert(n);
    std::cout << nums << '\n';
    
    std::cout << "\nRandom values: ";
    for (int num : rand_range(0, 500, 20)){
        std::cout << num << ' ';
        nums.insert(num);
    }
    std::cout << "\n\nTable after inserting above random values:\n" << nums << '\n';
    
    return 0;
}