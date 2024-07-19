#ifndef __QUEUE_H
#define __QUEUE_H

#include <iostream>

class Queue {
    public:
        Queue(size_t Size);
        void enqueue(int num);
        int dequeue();
        size_t capacity();
        int size();
        void resize(size_t Size);
        ~Queue();
    private:
        int* arr;
        int front;
        int rear;
        size_t s;
        bool is_empty();
        bool is_full();
        friend std::ostream& operator<<(std::ostream& output, Queue& q);
};

#endif // __QUEUE_H