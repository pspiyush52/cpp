/*
 * Sometimes we do not know the implementation of all functions in the base
 * class, such classes are called abstract classes and the virtual functions
 * for which the implementation is not known in the base class but which are
 * to be overridden in the derived classes are known as pure virtual
 * functions.
 * 
 * If a class contains even a single pure virtual function then it is known as
 * an abstract class. We cannot create objects of the abstract class type.
 * If a class derives from an abstract class it must provide an implementation
 * of all pure virtual functions or else it will become abstract too.
 */
#include "stream_insertable.h"
#include <typeinfo>

// List abstract class
template<typename T>
class List : public StreamInsertable{
    public:
        List() = default;
        virtual void append(T item) = 0;
        virtual T& operator[](size_t i) = 0;
        virtual const T& operator[](size_t i) const = 0;
        virtual size_t size() const = 0;
};

template<typename T>
class Llist;

template<typename T>
class __list_node{
    public:
        __list_node(T item) : data(item), next(nullptr){}
    private:
        T data;
        __list_node* next;
        friend class Llist<T>;
};

template<typename T>
class Llist : public List<T>{
    public:
        Llist() = default;
        void append(T item){
            __list_node<T>* new_node = new __list_node<T>{item};
            if (!head)
                head = new_node;
            else
            {
                new_node->next = head;
                head = new_node;
            }
            list_size++;
        }
        T& operator[](size_t i){
            if (i > (list_size - 1))
            {
                std::cerr<< "ERROR: List index out of bounds.\n";
                return error;
            }
            size_t j{};
            for (__list_node<T>* tmp = head; tmp; tmp = tmp->next, j++)
                if (i == j)
                    return (tmp->data);
            return error;
        }
        const T& operator[](size_t i) const {
            if (i > (list_size - 1))
            {
                std::cerr<< "ERROR: List index out of bounds.\n";
                return error;
            }
            size_t j{};
            for (__list_node<T>* tmp = head; tmp; tmp = tmp->next, j++)
                if (i == j)
                    return (tmp->data);
            return error;
        }
        size_t size() const { return list_size; }
        ~Llist(){
            __list_node<T>* tmp = head;
            while (head)
            {
                tmp = head->next;
                delete head;
                head = tmp;
            }
        }
        void stream_insert(std::ostream& output) const {
            if (list_size == 0)
                output << "[]";
            else
            {
                output << '[';
                __list_node<T>* tmp = head;
                for(; tmp->next; tmp = tmp->next)
                    output << tmp->data << ", ";
                output << tmp->data << ']';
            }
        }
    
    protected:
        __list_node<T>* head{nullptr};
        size_t list_size{};
        T error;
};

int main(void)
{
    Llist<int> nums;
    for (size_t i{}; i < 10; i++)
        nums.append(i);
    std::cout << "List nums: " << nums << '\n';
    std::cout << "nums[8]: "<< nums[8] << '\n';
    std::cout << "nums.size(): " << nums.size() << '\n';

    List<int>* ptr = &nums;
    ptr->append(23);
    std::cout << "List: " << *ptr << '\n';
    std::cout << "nums.size(): " << ptr->size() << '\n';

    return 0;
}