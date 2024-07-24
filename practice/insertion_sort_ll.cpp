#include "print.h"
#include "frand.h"

struct listNode {
    listNode(int k, listNode* n): key(k), next(n) {}
    listNode(int k): key(k), next(nullptr) {}
    int key;
    listNode* next;
};

class List {
    public:
        List() = default;
        bool isEmpty() const {
            return (!(this->head));
        }
        List& append(int item) {
            listNode* newNode = new listNode(item, this->head);
            this->head = newNode;
            return *this;
        }
        List& pop() {
            if (this->head) {
                listNode* tmp = head->next;
                delete this->head;
                this->head = tmp;
            }
            return *this;
        }
        List& sort() {
            this->insertionSort(this->head);
            // this->head = insertionSortIterative(this->head);
            // this->head = insertionSortIterative2(this->head);
            return *this;
        }
        ~List() {
            listNode* tmp{};
            for (; head; head = tmp) {
                tmp = head->next;
                delete head;
            }
            head = {};
        }
        listNode* getHead() {
            return this->head;
        }

        friend std::ostream& operator<<(std::ostream& out, const List& A) {
            out << '[';
            if (!A.isEmpty()) {
                listNode* head = A.head;
                for (; head->next; head = head->next)
                    out << head->key << ", ";
                out << head->key;
            }
            out << ']';
            return out;
        }
    private:
        listNode* head{};

        static void insertionSort(listNode* head) {
            if (head) {
                insertionSort(head->next);
                int key{head->key};
                for (; head->next && (key > head->next->key); head = head->next)
                    head->key = head->next->key;
                head->key = key;
            }
        }

        static listNode* insertionSortIterative(listNode* head) {
            if (head == nullptr || head->next == nullptr)
                return head;
            listNode* dummy = new listNode(0, head);
            listNode* curPrev = head;
            listNode* cur = head->next;
            listNode* prev = {};
            listNode* phead = {};
            while (cur) {
                prev = dummy;
                phead = dummy->next;
                while (phead != cur && phead->key < cur->key) {
                    prev = phead;
                    phead = phead->next;
                }
                if (phead != cur) {
                    curPrev->next = cur->next;
                    prev->next = cur;
                    cur->next = phead;
                    cur = curPrev->next;
                }
                else {
                    curPrev = cur;
                    cur = cur->next;
                }
            }
            listNode* sortedHead = dummy->next;
            delete dummy;
            return sortedHead;
        }
        static listNode* insertionSortIterative2(listNode* head) {
            if (head == nullptr || head->next == nullptr)
                return head;
            listNode* dummy = new listNode(0, head);
            listNode* curPrev = head;
            listNode* prev = {}, *tmp = {};
            while (curPrev->next) {
                prev = dummy;
                while (prev != curPrev && prev->next->key < curPrev->next->key)
                    prev = prev->next;
                if (prev != curPrev) {
                    tmp = curPrev->next->next;
                    curPrev->next->next = prev->next;
                    prev->next = curPrev->next;
                    curPrev->next = tmp;
                }
                else
                    curPrev = curPrev->next;
            }
            listNode* sortedHead = dummy->next;
            delete dummy;
            return sortedHead;
        }
};

int main(void)
{
    List nums;
    rng r;
    print(nums);
    repeat(10) nums.append(r.randint(-20, 100));
    print(nums);
    print(nums.sort());
    print(nums.sort());
    return 0;
}
