#ifndef __RANDOM_H
#define __RANDOM_H

#include <ctime>
#include <cstdlib>

#define __random_assigner (from + (std::rand() % (to-from)))

template<typename Container>
void shuffle(Container& con){
    std::srand(std::time(0));
    typename Container::value_type tmp{};
    for (size_t i{}, j{}, size{con.size()}; i < size; ++i){
        j = rand() % size;
        tmp = con[i];
        con[i] = con[j];
        con[j] = tmp;
    }
}

template<typename T>
void shuffle(T con[], size_t size){
    std::srand(std::time(0));
    T tmp{};
    for (size_t i{}, j{}; i < size; ++i){
        j = rand() % size;
        tmp = con[i];
        con[i] = con[j];
        con[j] = tmp;
    }
}

template<typename Container>
void push_random(Container& con, typename Container::value_type from, typename Container::value_type to, size_t size){
    std::srand(std::time(0));
    for (size_t i{}; i < size; ++i)
        con.push_back(__random_assigner);
}

template<typename Container>
void fill_random(Container& con, typename Container::value_type from, typename Container::value_type to){
    if (con.begin() == con.end())
        return;
    std::srand(std::time(0));
    auto iter = con.begin();
    for (; iter != con.end(); ++iter)
        *iter = (__random_assigner);
}

template<typename T>
void fill_random(T arr[], size_t size, T from, T to){
    for (size_t i{}; i < size; ++i)
        arr[i] = __random_assigner;
}

template<typename T>
void fill_random(T* begin, T* end, T from, T to){
    for (; begin != end; ++begin)
        *begin = __random_assigner;
}

template<typename ListContainer>
void append_random(ListContainer& list, typename ListContainer::value_type from, typename ListContainer::value_type to, size_t size){
    std::srand(std::time(0));
    for (size_t i{}; i < size; ++i)
        list.append(__random_assigner);
}

#endif  // __RANDOM_H
