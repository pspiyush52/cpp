#include "heap.h"

Heap::Heap(size_t size)
{
    if (size < 1)
    {
        std::cerr << "ERROR: Invalid Heap size." << std::endl;
        exit(1);
    }
    arr = new int[size];
    top = 0;
    s = size;
}

void Heap::insert(int num)
{
    if (top == (s - 1))
        __heap_resize__();
    
    arr[++top] = num;
    int cur = top, p = __parent__(cur);
    while(arr[p] > arr[cur])
    {
        if (p < 1)
            break;
        __arr_swap__(p, cur);
        cur = p;
        p = __parent__(cur);
    }
}

int Heap::pop()
{
    if (top < 1)
    {
        std::cerr << "ERROR: Heap empty." <<std::endl;
        Heap::~Heap();
        exit(1);
    }

    int num = arr[1];
    __arr_swap__(1, top);
    top--;
    __heapify__();
    return num;
}

void Heap::sort()
{
    if (top < 2)
        return;
    int init_top = top;
    repeat(init_top)
    {
        __arr_swap__(1, top);
        top--;
        __heapify__();
    }
    top = init_top;
}

void Heap::__heapify__()
{
    if (top == 2)
    {
        if (arr[1] > arr[2])
            __arr_swap__(1, 2);
        return;
    }
    
    int cur = 1, min_child = __min_child__(cur);
    if (!min_child)
        return;
    
    while (arr[cur] > arr[min_child])
    {
        __arr_swap__(cur, min_child);
        cur = min_child;
        min_child = __min_child__(cur);
        if (!min_child)
            return;
    }
}

int Heap::size()
{
    return top;
}

int Heap::__parent__(int n)
{
    return (n / 2);
}

int Heap::__left__(int n)
{
    return (2 * n);
}

int Heap::__right__(int n)
{
    return (2 * n + 1);
}

int Heap::__is_empty__()
{
    return (top == 0);
}

int Heap::__min_child__(int p)
{
    int l = 2 * p, r = 2 * p + 1;
    if (l == top)
        return l;
    if (r > top)
        return 0;
    return (arr[l] < arr[r]) ? l : r;
}

void Heap::__arr_swap__(int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

void Heap::__heap_resize__()
{
    int* new_arr = new int[2 * s];
    rrepeat(1, top + 1)
        new_arr[i] = arr[i];
    delete[] arr;
    arr = new_arr;
    s = 2 * s;
}

Heap::~Heap()
{
    delete[] arr;
    arr = nullptr;
    top = 0;
    s = 0;
}

std::ostream& operator<<(std::ostream& output, Heap& h)
{
    int top = h.top;
    if (!top)
        output << "[]";
    else
    {
        int* arr = h.arr;
        output << "[";
        rrepeat(1, top)
        {
            output << arr[i] << ", ";
        }
        output << arr[top] << "]";
    }
    return output;
}

int Heap::operator[](size_t i)
{
    if (i < 0 || i > (top - 1) || (top == 0))
    {
        std::cerr << "ERROR: Heap index out of bounds." << std::endl;
        Heap::~Heap();
        exit(1);
    }
    return arr[i + 1];
}
