#include "stack.h"

int main(void)
{
    Stack s(10);
    s.push(45);
    s.push(12);
    s.push(234);
    s.push(432);
    s.push(23);
    s.show_stack();
    return 0;
}