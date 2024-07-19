#include <iostream>
#include <exception>
#include <initializer_list>
#include "stream_insertable.h"
#include <type_traits>
#include <concepts>

template<typename T>
concept default_constructible = std::is_default_constructible_v<T>;

class IndexError : public std::out_of_range{
    public:
        IndexError():
            std::out_of_range(""){}
        const char* what() const noexcept {
            return "IndexError: List index out of bounds.";
        }
};

template<default_constructible T>
class List : public st::StreamInsertable<T>{
    public:
        List(size_t size = 16);
        List(std::initializer_list<T> args);
        // Making sure T is a copyable type before using the copy constructor
        List(const List& src) requires std::copyable<T>;
        List(List&& src);
        bool is_full() const;
        bool is_empty() const;
        void append(const T& item);
        void pop();
        size_t size() const;
        size_t capacity() const;
        void stream_insert(std::ostream& output) const override;
        void stream_insert_s(std::ostream& output) const override;
        T& operator[](size_t i);
        const T& operator[](size_t i) const;
        List& operator=(const List& rhs);
        List& operator=(List&& rhs);
        ~List();

    protected:
        T* arr;
        size_t list_size;
        size_t cur;
};

class item{
	public:
		item(int a, int b) : x(a), y(b){}
	private:
		int x;
		int y;
};

int main(void)
{
	List<int> l{12, 32, 45, 48, 13};
	std::cout << l << '\n';
	List<int> copy{l};
	std::cout << copy << '\n';

	// List<item> arr; // Error since item class has no default constructor
	return 0;
}

template<default_constructible T>
List<T>::List(size_t size) : arr(new T[size]), list_size(size), cur(0){}

template<default_constructible T>
List<T>::List(std::initializer_list<T> args) : List(args.size()){
    cur = args.size();
    T* _arr = arr;
    const T* start = args.begin();
    const T* end = args.end();
    while (start != end)
        (*(_arr++) = *(start++));
}

template<default_constructible T>
List<T>::List(const List<T>& src) requires std::copyable<T> : List(src.list_size){
    memcpy(arr, src.arr, list_size * sizeof(T));
    cur = src.cur;
}

template<default_constructible T>
List<T>::List(List<T>&& src) : List(src.list_size){
    memcpy(arr, src.arr, list_size * sizeof(T));
    cur = src.cur;
    delete[] src.arr;
    src.arr = nullptr;
    src.list_size = 0;
    src.cur = 0;
}

template<default_constructible T>
bool List<T>::is_full() const {
    return (cur == list_size);
}

template<default_constructible T>
bool List<T>::is_empty() const {
    return (!cur);
}

template<default_constructible T>
void List<T>::append(const T& item){
    if (is_full())
    {
        T* new_arr = new T[2 * list_size];
        memcpy(new_arr, arr, list_size * sizeof(T));
        delete[] arr;
        arr = new_arr;
        list_size *= 2;
    }
    arr[cur++] = item;
}

template<default_constructible T>
void List<T>::pop(){
    if (is_empty())
        std::cerr << "ERROR: List empty.\n";
    else
        cur--;
}

template<default_constructible T>
size_t List<T>::size() const { return cur; }

template<default_constructible T>
size_t List<T>::capacity() const { return list_size; }

template<default_constructible T>
T& List<T>::operator[](size_t i){
    if (i >= cur)
        throw IndexError();
    return arr[i];
}

template<default_constructible T>
const T& List<T>::operator[](size_t i) const{
    if (i >= cur)
        throw IndexError();
    return arr[i];
}

template<default_constructible T>
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

template<default_constructible T>
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

template<default_constructible T>
List<T>& List<T>::operator=(const List& rhs){
    delete[] arr;
    arr = new T[rhs.list_size];
    list_size = rhs.list_size;
    cur = rhs.cur;
    memcpy(arr, rhs.arr, list_size * sizeof(T));
    return *this;
}

template<default_constructible T>
List<T>& List<T>::operator=(List&& rhs){
    delete[] arr;
    arr = rhs.arr;
    list_size = rhs.list_size;
    cur = rhs.cur;
    rhs.arr = nullptr;
    rhs.list_size = 0;
    rhs.cur = 0;
    return *this;
}

template<default_constructible T>
List<T>::~List(){
    delete[] arr;
    arr = nullptr;
    list_size = 0;
}