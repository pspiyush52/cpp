#include <iostream>
#include <conio.h>
#include <exception>
#include "range.h"

class QueueFull : public std::exception{
    const char* what() const noexcept{
        return "Queue is full";
    }
};
class QueueEmpty : public std::exception{
    const char* what() const noexcept{
        return "Queue is empty";
    }
};

template<typename T>
class Queue{
    static const size_t DEFAULT_SIZE = 16;
    public:
        Queue() : Queue(DEFAULT_SIZE){}
        Queue(size_t size) : __arr(new T[size]), __size(size){}
        ~Queue(){
            delete[] __arr;
            __arr = nullptr;
            __size = 0;
        }
        bool empty() const{ return (__rear == -1); }
        bool full() const{ return (((__rear + 1) % __size) == __front); }
        Queue& enqueue(const T& item){
            if (this->full())
                throw QueueFull();
            if (this->empty())
                this->__front = 0;
            this->__rear = ((this->__rear + 1) % this->__size);
            this->__arr[this->__rear] = item;
            return *this;
        }
        Queue& dequeue(){
            if (this->empty())
                throw QueueEmpty();
            if (__front == __rear)
                this->__reset__();
            else
                __front = ((__front + 1) % __size);
            return *this;
        }
        const T& front() const{
            if (this->empty())
                throw QueueEmpty();
            return __arr[__front];
        }
        friend std::ostream& operator<<(std::ostream& output, const Queue& q){
            if (q.empty())
                output << "[]";
            else{
                output << '[' << q.front();
                if (q.__front != q.__rear){
                    size_t i = (q.__front + 1) % q.__size;
                    output << ", " << q.__arr[i];
                    for (; i != q.__rear; i = (i + 1) % q.__size)
                        output << ", " << q.__arr[i];
                }
                output << ']';
            }
            return output;
        }
    private:
        T* __arr;
        size_t __size;
        long long __front{-1};
        long long __rear{-1};
        void __reset__(){
            this->__front = -1;
            this->__rear = -1;
        }
};

int main(void)
{
    char ch;
    Queue<int> q;
    int num;
    rand_range rng(0, 100);
    rand_range::iterator iter = rng.begin();
    while (true){
        ch = getch();
        switch(ch)
        {
            case 'e':
                q.enqueue(*(++iter));
                break;
            case 'd':{
                num = q.front();
                std::cout << "Dequeued " << num << '\n';
                q.dequeue();
                break;
            }
            case 'x':
                return 0;
        }
        std::cout << q << '\n';
    }
    return 0;
}