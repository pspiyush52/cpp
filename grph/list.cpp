#include "list.h"

list_node::list_node(size_t Vertex, unsigned int Weight)
{
    v = Vertex;
    weight = Weight;
    next = nullptr;
}

list::list()
{
    head = nullptr;
    size = 0;
}

void list::insert(size_t v, unsigned int weight)
{
    if (!head)
        head = new list_node(v, weight);
    else
    {
        list_node* new_node = new list_node(v, weight);
        new_node->next = head;
        head = new_node;       
    }
    size++;
}

bool list::exists(size_t v)
{
    list_node* cur = head;
    for (; head; head = head->next)
        if (head->v == v)
            return true;
    return false;
}

size_t list::len()
{
    return size;
}

list::~list()
{
    if (!head)
        return;
    list_node* tmp = head;
    while (head != nullptr)
    {
        tmp = head->next;
        delete head;
        head = tmp;
    }
}

std::ostream& operator<< (std::ostream& output, list& l)
{
    if (l.head == nullptr)
        output << "[]";
    else
    {
        list_node* cur = l.head;
        output << "[";
        for (; cur->next; cur = cur->next)
            output << cur->v << ", ";
        output << cur->v << "]";
    }
    return output;
}