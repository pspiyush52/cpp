#ifndef __QUEUE_H
#define __QUEUE_H

#include "deque.h"
#include <exception>

class QueueEmpty : public std::length_error{
    QueueEmpty() : std::length_error("Queue empty"){}
    QueueEmpty(const char* msg) : std::length_error(msg){}
};

template<typename T>
class Queue{
    public:
        typedef                T         value_type;
        typedef                T*        pointer;
        typedef          const T*        const_pointer;
        typedef                T&        reference;
        typedef          const T&        const_reference;
    public:
        Queue() : dq(new deque<value_type>()){}
        Queue(long long size) : dq(new deque<value_type>(size)){}
        Queue(const Queue& src){
            if (src.dq)
                this->dq = new deque<value_type>(*(src.dq));
            else
                this->dq = new deque<value_type>();
        }
        Queue(Queue&& src){
            if (src.dq){
                this->dq = src.dq;
                src.dq = nullptr;
            }
            else
                this->dq = new deque<value_type>();
        }
        bool is_empty() const{
            return this->dq->is_empty();
        }
        Queue& enqueue(reference item){
            dq->push_back(std::forward<reference>(item));
            return *this;
        }
        Queue& enqueue(value_type&& item){
            dq->push_back(std::forward<value_type&&>(item));
            return *this;
        }
        Queue& dequeue(){
            dq->pop_front();
            return *this;
        }
        const_reference front() const{
            return this->dq->operator[](0);
        }
        ~Queue(){
            delete this->dq;
            this->dq = nullptr;
        }
        friend std::ostream& operator<<(std::ostream& output, const Queue& q){
            output << *(q.dq);
            return output;
        }
    private:
        deque<value_type>* dq;
};

#endif  // __QUEUE_H