#ifndef __STACK_H
#define __STACK_H

#include "iterator.h"

template<typename T>
class Stack{
    public:
        Stack() = default;
        Stack(const Stack& src);
        Stack(Stack&& src);
        bool is_empty();
        Stack& push(const T& item);
        Stack& push(T&& item);
        Stack& pop();
        const T& top();
        template<typename U>
        friend std::ostream& operator<<(std::ostream& output, const Stack<U>& s);
    private:
        List<T> data{};
};

template<typename T>
Stack<T>::Stack(const Stack& src) : data(src.data){}

template<typename T>
Stack<T>::Stack(Stack&& src) : data(src.data){
    src.data.invalidate();
}

template<typename T>
bool Stack<T>::is_empty(){
    return data.is_empty();
}

template<typename T>
Stack<T>& Stack<T>::push(const T& item){
    data.append(item);
    return *this;
}

template<typename T>
Stack<T>& Stack<T>::push(T&& item){
    data.append(std::move(item));
    return *this;
}

template<typename T>
Stack<T>& Stack<T>::pop(){
    if (data.is_empty())
        throw std::out_of_range("Stack Empty");
    data.pop_back();
    return *this;
}

template<typename T>
const T& Stack<T>::top(){
    if (data.is_empty())
        throw std::out_of_range("Stack Empty");
    return data.tail->node_data;
}

template<typename U>
std::ostream& operator<<(std::ostream& output, const Stack<U>& s){
    if (s.data.is_empty())
        output << "[()";
    else
    {
        output << "[(";
        typename List<U>::const_iterator iter = s.data.begin();
        typename List<U>::const_iterator upto = s.data.before_end();
        for (; iter != upto; ++iter)
            output << *iter << ", ";
        output << *iter << ')';
    }
    output << ", <Stack object at " << &s << ">]";
    return output;
}

#endif  // __STACK_H