#include "print.h"
class Object;
void __global_alloc_append__(Object* ptr);
class Object {
    public:
        virtual void streamInsert(std::ostream& out) const {
            out << "Object@" << this;
        }
        virtual ~Object() {}
        virtual constexpr int size() const {
            return 8;
        }
        void* operator new(size_t s) {
            void* ptr = malloc(s);
            __global_alloc_append__((Object*) ptr);
            return ptr;
        }
        void operator delete(void* ptr) {
            free(ptr);
        }

        friend std::ostream& operator<<(std::ostream& out, const Object& obj);
};
struct __gcollector_node {
    __gcollector_node(Object* ptr): optr{ptr} {}
    __gcollector_node(Object* ptr, __gcollector_node* nxt): optr{ptr}, next{nxt} {}
    ~__gcollector_node() {
        // std::cout << "Deleting " << (*(this->optr)) << '\n';
        delete this->optr;
        this->optr = {};
    }
    Object* optr{};
    __gcollector_node* next{};
};
struct __gcollector_node;
__gcollector_node* __global_allocs{};
void __global_alloc_append__(Object* ptr) {
    __gcollector_node* newNode = new __gcollector_node(ptr, __global_allocs);
    __global_allocs = newNode;
}
void clearHeap() {
    if (__global_allocs) {
        __gcollector_node* cur = __global_allocs;
        __gcollector_node* tmp{};
        while (cur) {
            tmp = cur->next;
            delete cur;
            cur = tmp;
        }
    }
}

class Integer : public Object {
    public:
        Integer(int n): num{n} {}
        Integer(const char* str) {
            this->num = 0;
            for (; *str; ++str) {
                this->num = (this->num * 10) + (*str - 48);
            }
        }
        Integer operator+(const Integer& x) const {
            return {this->num + x.num};
        }
        Integer operator+(const int& x) const {
            return {this->num + x};
        }
        Integer& operator+=(const Integer& x) {
            this->num += x.num;
            return *this;
        }
        Integer& operator+=(const int& x) {
            this->num += x;
            return *this;
        }
        friend Integer operator+(const int& x, const Integer& y) {
            return {x + y.num};
        }
        friend int& operator+=(int& x, const Integer& y) {
            x += y.num;
            return x;
        }
        Integer operator-(const Integer& x) const {
            return {this->num - x.num};
        }
        Integer operator-(const int& x) const {
            return {this->num - x};
        }
        Integer& operator-=(const Integer& x) {
            this->num -= x.num;
            return *this;
        }
        Integer& operator-=(const int& x) {
            this->num -= x;
            return *this;
        }
        friend Integer operator-(const int& x, const Integer& y) {
            return {x - y.num};
        }
        friend int& operator-=(int& x, const Integer& y) {
            x -= y.num;
            return x;
        }
        Integer operator*(const Integer& x) const {
            return {this->num * x.num};
        }
        Integer operator*(const int& x) const {
            return {this->num * x};
        }
        Integer& operator*=(const Integer& x) {
            this->num *= x.num;
            return *this;
        }
        Integer& operator*=(const int& x) {
            this->num *= x;
            return *this;
        }
        friend Integer operator*(const int& x, const Integer& y) {
            return {x * y.num};
        }
        friend int& operator*=(int& x, const Integer& y) {
            x += y.num;
            return x;
        }
        Integer operator/(const Integer& y) const {
            return {this->num / y.num};
        }
        Integer operator/(const int& y) const {
            return {this->num / y};
        }
        Integer& operator/=(const Integer& y) {
            this->num /= y.num;
            return *this;
        }
        Integer& operator/=(const int& y) {
            this->num /= y;
            return *this;
        }
        friend Integer operator/(const int& x, const Integer& y) {
            return {x + y.num};
        }
        friend int& operator/=(int& x, const Integer& y) {
            x /= y.num;
            return x;
        }
        // void* operator new(size_t s) {
        //     void* ptr = malloc(s);
        //     __global_alloc_append__((Object*) ptr);
        //     return ptr;
        // }
    
    private:
        int num;

        void streamInsert(std::ostream& out) const {
            out << this->num;
        }
};
class String : public Object {
    static const int DEFAULT_SIZE{8};
    public:
        String(): A{new char[DEFAULT_SIZE]}, n{DEFAULT_SIZE} {}
        String(const char* str): String() {
            for (; *str; ++str)
                this->append(*str);
        }
        bool isEmpty() const {
            return (!(this->cur));
        }
        String& append(const char& ch) {
            if (this->isFull())
                this->expand();
            this->A[(this->cur)++] = ch;
            return *this;
        }
        
        ~String() {
            if (this->A) {
                delete[] this->A;
                this->A = {};
                this->cur = {};
                this->n = {};
            }
        }
    private:
        char* A;
        int cur{};
        int n{DEFAULT_SIZE};

        void streamInsert(std::ostream& out) const {
            out << '"';
            if (!this->isEmpty()) {
                for (int i{}; i < this->cur; ++i)
                    out << this->A[i];
            }
            out << '"';
        }
        bool isFull() const {
            return (this->cur == this->n);
        }
        void expand() {
            char* newArray = new char[this->n * 2];
            memcpy(newArray, this->A, this->cur);
            delete[] this->A;
            this->A = newArray;
            this->n *= 2;
        }
};
class __list_node {
    friend class List;
    public:
        __list_node(Object* obj, __list_node* Prev, __list_node* Next):
            ptr{obj}, prev{Prev}, next{Next} {}
        __list_node(Object* obj): __list_node(obj, {}, {}) {}
        ~__list_node() {
            if (this->ptr) {
                delete this->ptr;
                this->ptr = {};
            }
        }
    
    private:
        Object* ptr;
        __list_node* prev;
        __list_node* next;
};
class List : public Object {
    typedef __list_node ListNode;
    public:
        List() {
            this->head = new ListNode(new Object());
            this->tail = new ListNode(new Object());
            this->head->next = this->tail;
            this->tail->prev = this->head;
        }
        List(std::initializer_list<Object*> items): List() {
            auto iter = items.begin();
            for (; iter != items.end(); ++iter)
                this->append(*iter);
        }
        bool isEmpty() const {
            return (this->head->next == this->tail);
        }
        List& append(Object* item) {
            ListNode* newNode = new ListNode(item, this->tail->prev, this->tail);
            this->tail->prev->next = newNode;
            this->tail->prev = newNode;
            return *this;
        }
        ~List() {
            if (this->head) {
                ListNode* cur = this->head;
                ListNode* tmp{};
                for (; cur; cur = cur->next) {
                    tmp = cur->next;
                    delete cur;
                    cur = tmp;
                }
            }
        }

    private:
        ListNode* head;
        ListNode* tail;
        void streamInsert(std::ostream& out) const {
            out << "[";
            if (!this->isEmpty()) {
                ListNode* cur = this->head->next;
                for (; cur != this->tail->prev; cur = cur->next)
                    out << *(cur->ptr) << ", ";
                out << *(cur->ptr);
            }
            out << "]";
        }
};

class ArrayList : public Object {
    static const int DEFAULT_SIZE{8};
    public:
        ArrayList(): A{new Object*[DEFAULT_SIZE]}, cur{}, n{DEFAULT_SIZE} {}
        ArrayList(int size) {
            size = (size < DEFAULT_SIZE) ? DEFAULT_SIZE : size;
            this->A = new Object*[size];
            this->cur = {};
            this->n = size;
        }
        ArrayList(std::initializer_list<Object*> items): ArrayList(2 * items.size()) {
            auto iter = items.begin();
            for (int i{}; iter != items.end(); ++iter, ++i)
                this->A[i] = *iter;
            this->cur = items.size();
        }
        bool isEmpty() const {
            return (!this->cur);
        }
        constexpr int size() const {
            return this->cur;
        }
        ArrayList& append(Object* item) {
            if (this->isFull())
                this->expand();
            this->A[(this->cur)++] = item;
            return *this;
        }
        Object& operator[](int i) {
            if (i >= this->cur)
                throw std::out_of_range("List Index out of bounds");
            return *(this->A[i]);
        }
        ~ArrayList() {

        }
    private:
        Object** A;
        int cur;
        int n;

        bool isFull() const {
            return this->cur == this->n;
        }
        void expand() {
            Object** newArray = new Object*[this->n * 2];
            memcpy(newArray, A, this->cur * sizeof(Object*));
            delete[] this->A;
            this->A = newArray;
            this->n *= 2;
        }
        void streamInsert(std::ostream& out) const {
            out << "[";
            if (!this->isEmpty()) {
                int i{};
                for (; i < this->cur - 1; ++i)
                    out << *(this->A[i]) << ", ";
                out << *(this->A[i]);
            }
            out << "]";
        }
};

int main(int argc, const char* argv[])
{
    ArrayList li;
    li
        .append(new Integer{12})
        .append(new Integer{87})
        .append(new ArrayList{new Integer{23}, new Integer{7}, new Integer{19}})
        .append(new String{"What is this"})
        .append(new Integer{8});
    print(li);
    print(li[2]);
    print(li[2].size());
    clearHeap();
    return 0;
}

std::ostream& operator<<(std::ostream& out, const Object& obj) {
    obj.streamInsert(out);
    return out;
}
