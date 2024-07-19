#include "queue.h"

Queue::Queue(size_t Size)
{
    s = Size;
    arr = new int[Size];
    front = rear = -1;
}

bool Queue::is_empty()
{
    return (front == -1);
}

bool Queue::is_full()
{
    return ((rear + 1) % s == front);
}

void Queue::enqueue(int num)
{
    if (is_full())
    {
        std::cerr << "OVERFLOW ERROR: Queue full." << std::endl;
        return;
    }
    if (is_empty())
        front = rear = 0;
    else
        rear = (rear + 1) % s;
    arr[rear] = num;
}

int Queue::dequeue()
{
    if (is_empty())
    {
        std::cerr << "UNDERFLOW ERROR: Queue empty." << std::endl;
        return INT_MIN;
    }

    int dequeued = arr[front];
    if (front == rear)
        front = rear = -1;
    else
        front = (front + 1) % s;
    return dequeued;
}

size_t Queue::capacity()
{
    return s;
}

int Queue::size()
{
    if (is_empty())
        return 0;
    if (front < rear)
        return ((rear - front) + 1);
    else if (front > rear)
        return ((s + 1) - (front - rear));
    else
        return 1;
}

void Queue::resize(size_t Size)
{
    if (Size == 0)
    {
        std::cerr << "ERROR: Cannot resize to size zero." << std::endl;
        return;
    }
    if (Size < size())
    {
        std::cerr << "ERROR: Resizing Queue to be shorter than data size. Data loss is liable to occur." << std::endl;
        return;
    }
    if (is_empty())
    {
        delete[] arr;
        arr = new int[Size];
    }
    else
    {
        int arr_size = size(), i = 0;
        int* new_arr = new int[Size];
        for (; i < arr_size; i++)
            new_arr[i] = arr[i];
        delete[] arr;
        arr = new_arr;
    }
    s = Size;
}

Queue::~Queue()
{
    delete[] arr;
}

std::ostream& operator<<(std::ostream& output, Queue& q)
{
    if (q.is_empty())
        output << "Queue([])";
    else
    {
        int i{q.front};
        output << "Queue([";
        for (; i != q.rear; i = (i + 1) % q.s)
            output << q.arr[i] << ", ";
        output << q.arr[i] << "])";
    }
    return output;
}