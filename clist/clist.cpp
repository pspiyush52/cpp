#include "clist.h"
#include <stdlib.h>

List::List()
{
    tail = nullptr;
    size = 0;
}

void List::append(int num)
{
    if (tail == nullptr)
    {
        tail = create(num);
        tail->next = tail;
    }
    else
    {
        node* new_node = create(num);
        new_node->next = tail->next;
        tail->next = new_node;
        tail = new_node;
    }
    size++;
}

size_t List::find(int num)
{
    if (tail == nullptr)
    {
        std::cout << "ERROR: Trying to search for an element in an empty list.\n";
        return ULLONG_MAX;
    }
    char flag = 0;
    size_t index = 0;
    node* head = tail->next;
    for (; head != tail; head = head->next, index++)
        if (head->num == num)
            return index;
    if (tail->num == num)
        return (size - 1);
    return ULLONG_MAX;
}

int& List::operator[](long long i)
{
    if (i < 0)
        i = size + i;
    if (i > (size - 1) || (size == 0))
    {
        std::cout << "ERROR: List index out of bounds.\n";
        exit(1);
    }
    node* head = tail->next;
    long long j;
    repeat(i, j)
        head = head->next;
    return (head->num);
}

std::ostream& operator<<(std::ostream& output, List& l)
{
    if (!(l.len()))
    {
        output << "[]";
        return output;
    }
    node* tail = l.__get_tail__();
    node* head = tail->next;
    output << "[";
    for (; head != tail; head = head->next)
        output << head->num << ", ";
    output << tail->num  << "]";
    return output;
}

void List::display()
{
    if (tail == nullptr)
    {
        std::cout << "[]";
        return;
    }
    node* head = tail->next;
    std::cout << "[";
    for (; head != tail; head = head->next)
        std::cout << head->num << ", ";
    std::cout << tail->num << "]";
}

int List::pop()
{
    if (!size)
    {
        std::cout <<"ERROR: List empty.\n";
        return INT_MAX;
    }
    int val = tail->num;
    node* tmp = tail->next;
    for (; tmp->next != tail; tmp = tmp->next);
    tmp->next = tail->next;
    delete tail;
    tail = tmp;
    return val;
}

size_t List::len()
{
    return size;
}

node* List::__get_tail__()
{
    return tail;
}

List::~List()
{
    if (tail == nullptr)
        return;
    node* head = tail->next;
    node* tmp = nullptr;
    while (head != tail)
    {
        tmp = head->next;
        free(head);
        head = tmp;
    }
    free(tail);
    tail = nullptr;
    size = 0;
}

int error(size_t val)
{
    int flag = 0;
    switch (val)
    {
        case ULLONG_MAX:
        case INT_MAX:
            flag = 1;
    }
    return flag;
}