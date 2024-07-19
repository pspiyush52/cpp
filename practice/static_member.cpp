#include "static_member.h"

int main(void)
{
    Array arr{4, 2, 5, 1};
    std::cout << "arr.size() : " << arr.size() << '\n';
    std::cout << "arr.capacity() : " << arr.capacity() << '\n';
    Array arr2;
    Array arr3(10);
    Array arr4(std::move(Array{3, 4, 1, 5, 78, 5, 63, 17, 2}));
    std::cout << arr4 << '\n';
    arr[4];
    return 0;
}

Array::Array():
    Array(16){}

Array::Array(size_t size):
    arr(new int[size]), Size(size), cur(0){
        _A_list._append(this);
    }

Array::Array(std::initializer_list<int> args){
    Size = args.size();
    arr = new int[Size];
    cur = 0;
    _A_list._append(this);
    if (args.size())
    {
        for (int arg : args)
            append(arg);
    }
}

// move constructor
Array::Array(Array&& source_arr):
    arr(source_arr.arr), Size(source_arr.Size), cur(source_arr.cur){
        source_arr.arr = nullptr;
    }

bool Array::is_full(){
    return (cur == Size);
}

bool Array::is_empty(){
    return (cur == 0);
}

void Array::append(int item)
{
    if (is_full())
    {
        int* new_arr = new int[2 * Size];
        for (size_t i{}; i < Size; i++)
            new_arr[i] = arr[i];
        Size *= 2;
        delete arr;
        arr = new_arr;
    }
    arr[cur++] = item;
}

size_t Array::capacity(){
    return this->Size;
}

size_t Array::size(){
    return this->cur;
}

int& Array::operator[](size_t i)
{
    if (i >= cur)
    {
        std::cerr << "ERROR: Array index out of bounds.\n";
        _A_list.clear_list();
        exit(0);
    }
    return arr[i];
}

void Array::swap(size_t i, size_t j){
    if (i >= cur || j >= cur)
    {
        std::cerr << "\nERROR: Array index out of bounds.\n";
        return;
    }
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

void Array::release(){
    delete[] arr;
    arr = nullptr;
}

_arr_node::_arr_node(Array* A){
    this->A = A;
    this->next = nullptr;
}

_arr_list::_arr_list():
    head(nullptr){}

void _arr_list::_append(Array* A){
    _arr_node* new_node = new _arr_node(A);
    if (head == nullptr)
        head = new_node;
    else
    {
        new_node->next = head;
        head = new_node;
    }
}

void _arr_list::clear_list(){
    if (head == nullptr)
        return;
    _arr_node* tmp = nullptr;
    while (head)
    {
        tmp = head->next;
        head->A->release();
        delete head;
        head = tmp;
    }
}

std::ostream& operator<<(std::ostream& output, Array& A)
{
    if (A.is_empty())
        output << "[]";
    else
    {
        size_t i{};
        output << "[";
        for (; i < A.cur - 1; i++)
            output << A.arr[i] << ", ";
        output << A.arr[i] << "]";
    }
    return output;
}