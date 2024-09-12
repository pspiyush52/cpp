#include "print.h"
#include "string.h"
#include "exceptions.h"
#include "..\deque\deque.h"

class List {
    public:
        virtual constexpr size_t size() const noexcept = 0;
        virtual List& append(int val) = 0;
        virtual List& pop() = 0;
        virtual size_t search(int key) const noexcept = 0;
        virtual ~List() = default;

        friend std::ostream& operator<<(std::ostream& out, const List& l) {
            l.streamInsert(out);
            return out;
        }
    private:
        virtual void streamInsert(std::ostream& out) const noexcept = 0;
};
class ArrayList : public List {
    public:
        ArrayList(): arr{new int[8]}, cur{}, arrSize{} {}
        ArrayList(size_t size) {
            size = (size < 8) ? 8 : size;
            this->arr = new int[size];
            this->cur = {};
            this->arrSize = size;
        }
        virtual constexpr size_t size() const noexcept {
            return this->cur;
        }
        virtual List& append(int val) {
            if (this->isFull())
                this->__alter(EXPAND);
            this->arr[this->cur] = val;
            ++(this->cur);
            return *this;
        }
        virtual List& pop() {
            --(this->cur);
            if (this->isVacant())
                this->__alter(SHRINK);
            return *this;
        }
        virtual size_t search(int key) const noexcept {
            for (size_t i{}; i < this->cur; ++i)
                if (this->arr[i] == key)
                    return i;
            return ULLONG_MAX;
        }
        ~ArrayList() {
            delete[] this->arr;
            this->arr = {};
            this->cur = {};
            this->arrSize = {};
        }

    private:
        int* arr{};
        size_t cur{};
        size_t arrSize{};
        static constexpr int EXPAND{0};
        static constexpr int SHRINK{1};

        virtual void streamInsert(std::ostream& out) const noexcept {
            out << "<ArrayList@" << this << '[';
            if (this->cur) {
                size_t i{};
                for (; i < this->cur - 1; ++i)
                    out << this->arr[i] << ", ";
                out << this->arr[i];
            }
            out << "]>";
        }
        constexpr bool isFull() const noexcept {
            return this->cur == this->arrSize;
        }
        constexpr bool isVacant() const noexcept {
            return (this->arrSize > 8) && (this->cur <= (this->arrSize / 3));
        }
        void __alter(int flag) {
            size_t newSize{};
            switch(flag) {
                case EXPAND:
                    newSize *= 2;
                    break;
                case SHRINK:
                    newSize /= 2;
            }
            int* newArray = new int[newSize];
            memcpy(newArray, this->arr, this->cur * sizeof(int));
            delete[] this->arr;
            this->arr = newArray;
            this->arrSize = newSize;
        }
};
class LList : public List {
    struct ListNode {
        ListNode(int n): val{n}, next{nullptr} {}
        ListNode(int n, ListNode* Next): val{n}, next{Next} {}
        int val;
        ListNode* next;
    };
    public:
        LList(): head{new ListNode{0}}, tail{head}, listSize{} {}
        virtual constexpr size_t size() const noexcept {
            return this->listSize;
        }
        virtual List& append(int val) {
            ListNode* newNode = new ListNode{val};
            this->tail->next = newNode;
            this->tail = newNode;
            ++(this->listSize);
            return *this;
        }
        virtual List& pop() {
            if (!this->isEmpty()) {
                ListNode* h = this->head->next;
                this->head->next = h->next;
                delete h;
                --(this->listSize);
            }
            return *this;
        }
        virtual size_t search(int key) const noexcept {
            if (this->isEmpty())
                return ULLONG_MAX;
            size_t pos{};
            for (ListNode* cur = this->head->next; cur; cur = cur->next, ++pos)
                if (cur->val == key)
                    return pos;
            return ULLONG_MAX;
        }
        ~LList() {
            if (this->head) {
                ListNode* cur = this->head;
                for (ListNode* tmp{}; cur; cur = tmp) {
                    tmp = cur->next;
                    delete cur;
                }
            }
        }

    private:
        ListNode* head;
        ListNode* tail;
        size_t listSize{};

        constexpr bool isEmpty() const noexcept {
            return this->head == nullptr;
        }
        virtual void streamInsert(std::ostream& out) const noexcept {
            out << "<LList@" << this << '[';
            if (!(this->isEmpty())) {
                for (ListNode* cur = this->head->next; cur != this->tail; cur = cur->next)
                    out << cur->val << ", ";
                out << this->tail->val;
            }
            out << ">]";
        }
};
class NullList : public List {
    public:
        virtual constexpr size_t size() const noexcept {
            return {};
        }
        virtual List& append(int) {
            throw NullStateException();
        }
        virtual List& pop() {
            throw NullStateException();
        }
        virtual size_t search(int) const noexcept {
            return ULLONG_MAX;
        }
    private:
        void streamInsert(std::ostream& out) const noexcept {
            out << "Null";
        }
};
class ListFactory {
    public:
        ListFactory() = default;
        List& getList(const String& listType) {
            return *(this->__getList(listType));
        }
        List* __getList(const String& listType) {
            List* ptr{};
            if (listType.similar("arraylist"))
                ptr = new ArrayList{};
            else if (listType.similar("linkedlist"))
                ptr = new LList{};
            else
                ptr = new NullList{};
            lists.push_back(ptr);
            return ptr;
        }
        ~ListFactory() {
            for (auto& ptr : lists)
                delete ptr;
        }
    private:
        deque<List*> lists{};
};

int main(void)
{
    ListFactory f{};
    List& l = f.getList("arrayList");
    // List&& l = LList{};
    l.append(12).append(15).append(17);
    print(l);
    return 0;
}
