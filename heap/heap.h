/* 
 * An implementation of a Min-Heap data structure with heap sort algorithm
 * implemented in the same class.
 * 
 * The heap can be initialized with any positive non-zero size and will
 * continue to grow as the size of the data grows.
 * 
 * At any point the pop() method will delete and return the minimum element
 * of the heap which is also the first element.
 * If there are no elements left it will throw an error and exit.
 * 
 * WARNING: Even if the size of data reduces by repeated calls of pop(), the
 * heap will not shrink in size. That is, once the heap has grown to a certain
 * size then even if the data in the heap is reduced the heap will continue to
 * occupy the grown size in memory.
 * 
 * The sort() method sorts the data in descending order in place.
 * 
 * The size() method returns the total number of elements in the heap and not
 * the actual size occupied by the heap in memory.
 * 
 * The array operator [] can be used to access any item in the heap but it is
 * read only and the value cannot be modified by assignment.
 * If the index is out of bounds it will throw an error and exit.
 * 
 * This  -->   arr[i] = value      is not allowed.
 * 
 * The heap can be directly displayed via the output stream using the <<
 * operator.
 */

#ifndef __HEAP_H
#define __HEAP_H

#include <iostream>

#ifdef repeat
#undef repeat
#endif

#ifdef repeati
#undef repeati
#endif

#ifdef rrepeat
#undef rrepeat
#endif

// Use this macro to repeat any set of instructions N number of times.
#define repeat(N) for (int i = 0; i < N; i++)

// Use this macro to repeat any set of instructions N number of times using
// a pre-declared control variable i.
#define repeati(N, i) for (i = 0; i < N; i++)

// Use this macro to run a loop with the control variable's values starting
// from 'start' and goind up to 'end'.
#define rrepeat(start, end) for (int i = start; i < end; i++)

// A macro to print a newline anywhere in the program.
#ifndef nl
#define nl std::cout << std::endl;
#endif

class Heap {
    public:
        Heap(size_t size);
        void insert(int num);  // insert num into the heap
        int pop();  // Delete and return the first element of the heap which is the minimum element as well.
        void sort();  // Do a heap sort. Items will be sorted in descending order.
        int size();  // Return the number of elements currently in the heap.
        int operator[](size_t);  // To provide read only access via the index:- [] operator.
        ~Heap();
    private:
        int* arr;
        int top;
        size_t s;
        int __is_empty__();
        int __parent__(int);
        int __left__(int);
        int __right__(int);
        int __min_child__(int);
        void __arr_swap__(int, int);
        void __heap_resize__();
        void __heapify__();
        friend std::ostream& operator<<(std::ostream& output, Heap& h);
};

#endif // __HEAP_H