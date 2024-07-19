#include <iostream>
#include <concepts>
#include <limits>
#include "range.h"
#define SIZE 11
#define SHOW_NULL

template<std::integral T>
class table{
    public:
        table() : __arr(new T[SIZE]), __size(SIZE){
            T* end = __arr + __size;
            for (T* iter = __arr; iter != end; ++iter)
                *iter = this->null;
        }
        table& insert(const T item){
            if (this->__load__() >= this->__max_load)
                this->__expand__();
            size_t pos = __hash_fun__(item);
            if (!__is_empty__(pos)){
                size_t i{pos};
                for (; !__is_empty__(i); i = (i + 1) % this->__size);
                pos = i;
            }
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
        size_t __count{};
        static inline T null{std::numeric_limits<T>::min()};
        static inline double __max_load{0.75};

        size_t __hash_fun__(const T item){
            return (item % __size);
        }
        bool __is_empty__(size_t pos){
            return (this->__arr[pos] == null);
        }
        double __load__(){
            return (1.0 * this->__count / this->__size);
        }
        void __expand__(){
            T* cur_arr{this->__arr};
            size_t cur_size{this->__size};
            this->__size *= 2;
            T* tmp = new T[this->__size];

            T* tmp_end = tmp + this->__size;
            for (T* tmp_iter = tmp; tmp_iter != tmp_end; ++tmp_iter)
                *tmp_iter = null;
            
            this->__arr = tmp;
            __rehash__(cur_arr, tmp, cur_size);
            delete[] cur_arr;
        }
        void __rehash__(T* __cur, T* __new, size_t __cur_size){
            for (size_t i{}, pos{}; i < __cur_size; ++i, pos = i){
                if (!__is_empty__(pos)){
                    size_t j{pos};
                    std::cout << "here\n";
                    for (; !__is_empty__(j); j = (j + 1) % this->__size)
                        std::cout << j << '\n';
                    pos = j;
                }
                __new[pos] = __cur[i];
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
    table<int> nums;
    std::cout << nums << '\n';

    for (int n : {1, 34, 2238})
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