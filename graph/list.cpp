#include "list.h"

list_node::list_node(size_t num, unsigned int Weight)
{
    v = num;
    weight = Weight;
    next = nullptr;
}

List::List()
{
    head = nullptr;
    size = 0;
}

void List::insert(size_t v, unsigned int weight)
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

size_t List::len()
{
    return size;
}

void List::remove(size_t v)
{
    if (!head)
    {
        std::cerr << "ERROR: List empty." << std::endl;
        return;
    }

    list_node* tmp = head;
    if (head->v == v)
    {
        head = head->next;
        delete tmp;
        return;
    }
    
    list_node* trailing = NULL;
    for (; tmp; tmp = tmp->next)
    {
        trailing = tmp;
        if (tmp->v == v)
        {
            trailing->next = tmp->next;
            delete tmp;
            return;
        }
    }
    std::cerr << "ERROR: " << v << " does not exist in the list." << std::endl;
}

size_t List::pop()
{
    if (!head)
    {
        std::cerr << "ERROR: List empty." << std::endl;
        return LLONG_MAX;
    }
    size_t v = head->v;
    head = head->next;
    return v;
}

std::ostream& operator<<(std::ostream& output, List& l)
{
    if (!l.head)
        output << "[]";
    else
    {
        list_node* tmp = l.head;
        output << "[";
        for (; tmp->next; tmp = tmp->next)
            output << tmp->v << ", ";
        output << tmp->v << "]";
    }
    return output;
}

List::~List()
{
    if (!head)
        return;
    list_node* tmp = head;
    for (; head; head = tmp)
    {
        tmp = head->next;
        delete head;
    }
    head = NULL;
    size = 0;
}