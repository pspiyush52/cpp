#include <iostream>
using namespace std;
class Stack
{
    private:
        unsigned int size;
        int top;
        int* arr;
        int is_full();
        int is_empty();
    public:
        Stack(unsigned int);
        ~Stack();
        int peek();
        void push(int);
        int pop();
        void show_stack();
};

Stack::Stack(unsigned int s)
{
    size = s;
    top = -1;
    arr = new int[s];
}

Stack::~Stack()
{
    delete[] arr;
}

int Stack::is_full()
{
    return (top == size-1);
}

int Stack::is_empty()
{
    return (top == -1);
}

int Stack::peek()
{
    return arr[top];
}

void Stack::push(int n)
{
    if (!is_full())
        arr[++top] = n;
    else
        cout << "Overflow!\n";
}

int Stack::pop()
{
    if (is_empty())
    {
        cout << "Underflow!\n";
        return INT_MIN;
    }
    else
        return arr[top--];
}

void Stack::show_stack()
{
    if (is_empty())
        return;
    int i;
    cout << "\t[" << arr[top] << "] <-- top" << endl;
    for (i = top - 1; i > -1; i--)
        cout << "\t[" << arr[i] << "]" <<endl;
}