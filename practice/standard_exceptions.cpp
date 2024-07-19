#include <iostream>
#include <exception>
#include <initializer_list>
#include "stream_insertable.h"
#include "utils.h"

class IndexError : public std::out_of_range{
    public:
        IndexError():
            std::out_of_range(""){}
        const char* what() const noexcept {
            return "IndexError: List index out of bounds.";
        }
};

template<typename T>
class List : public st::StreamInsertable<T>{
    public:
        List(size_t size = 16);
        List(std::initializer_list<T> args);
        bool is_full() const;
        bool is_empty() const;
        void append(const T& item);
        void pop();
        size_t size() const;
        size_t capacity() const;
        T& operator[](size_t i);
        const T& operator[](size_t i) const;
        void stream_insert(std::ostream& output) const override;
        void stream_insert_s(std::ostream& output) const override;
        ~List();

    protected:
        T* arr;
        size_t list_size;
        size_t cur;
};

int main(int argc, char* argv[])
{
    std::set_terminate(&custom_terminate);

    List<int> nums(100);
    for (size_t i{}; i < 20; i++)
        nums.append(i * i);
    std::cout << "The list: " << nums << '\n';
    std::cout << "List size: " << nums.size() << '\n';
    std::cout << "Total capacity: " << nums.capacity() << '\n';
    std::cout << "nums[12]: " << nums[12] << '\n';
    try{
        std::cout << "nums[49]: " << nums[49] << '\n';
    }
    catch(std::length_error& ex){
        std::cout << ex.what() << '\n';
    }

    const List<const char*> names{
        "Niharika Joshi", "Piyush Singh", "Pratima Joshi", "Milan Singh",
        "Pranjai Bhatt", "Ankit Singh", "Rahul Singh"
    };
    std::cout << names << '\n';
    std::cout << "#1 Name: " << names[0] << '\n';

    return 0;
}

template<typename T>
List<T>::List(size_t size) : arr(new T[size]), list_size(size), cur(0){}

template<typename T>
List<T>::List(std::initializer_list<T> args) : List(args.size()){
    cur = args.size();
    T* _arr = arr;
    const T* start = args.begin();
    const T* end = args.end();
    while (start != end)
        (*(_arr++) = *(start++));
}

template<typename T>
bool List<T>::is_full() const {
    return (cur == list_size);
}

template<typename T>
bool List<T>::is_empty() const {
    return (!cur);
}

template<typename T>
void List<T>::append(const T& item){
    if (is_full())
    {
        T* new_arr = new T[2 * list_size];
        memcpy(new_arr, arr, list_size);
        list_size *= 2;
    }
    arr[cur++] = item;
}

template<typename T>
void List<T>::pop(){
    if (is_empty())
        std::cerr << "ERROR: List empty.\n";
    else
        cur--;
}

template<typename T>
size_t List<T>::size() const { return cur; }

template<typename T>
size_t List<T>::capacity() const { return list_size; }

template<typename T>
T& List<T>::operator[](size_t i){
    if (i >= cur)
        throw IndexError();
    return arr[i];
}

template<typename T>
const T& List<T>::operator[](size_t i) const{
    if (i >= cur)
        throw IndexError();
    return arr[i];
}

template<typename T>
void List<T>::stream_insert(std::ostream& output) const {
    if (cur == 0)
        output << "[]";
    else
    {
        size_t i{}, upto{cur - 1};
        output << '[';
        for (; i < upto; i++)
            output << arr[i] << ", ";
        output << arr[i] << ']';
    }
}

template<>
void List<char>::stream_insert(std::ostream& output) const {
    if (cur == 0)
        output << "[]";
    else
    {
        size_t i{}, upto{cur - 1};
        output << '[';
        for (; i < upto; i++)
            output << '\'' << arr[i] << "\', ";
        output << '\'' << arr[i] << "\']";
    }
}

template<typename T>
void List<T>::stream_insert_s(std::ostream& output) const{
    if (cur == 0)
        output << "[]";
    else
    {
        size_t i{}, upto{cur - 1};
        output << '[';
        for (; i < upto; i++)
            output << '\"' << arr[i] << "\", ";
        output << '\"' << arr[i] << "\"]";
    }    
}

template<typename T>
List<T>::~List(){
    delete[] arr;
    arr = nullptr;
    list_size = 0;
}