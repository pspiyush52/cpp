#include "print.h"

struct _greater {
    template<typename T>
    bool operator()(const T& left, const T& right) {
        return (left > right);
    }
};

template<typename value_tp, typename comp = _greater>
class Heap {
    static const int DEFAULT_SIZE{8};
    typedef     value_tp     value_type;
    typedef     value_tp*    pointer;

    public:
        Heap(int size, comp comparator = {}) {
            size = (size < DEFAULT_SIZE) ? DEFAULT_SIZE : size;
            this->_arr = new value_tp[size];
            this->_n = {};
            this->_size = size;
            this->_comp = comparator;
        }
        Heap(comp comparator): Heap(0, comparator) {}
        Heap(): Heap(0) {}
        Heap(const Heap& src) = delete;
        Heap(Heap&& src) {
            this->_arr = src._arr;
            this->_n = src._n;
            this->_size = src._size;
            src._arr = {};
        }
        bool isFull() {
            return (this->_n == this->_size);
        }
        bool isEmpty() {
            return (this->_n == 0);
        }
        Heap& insert(const value_tp& item) {
            if (this->isFull())
                this->__expand__();
            this->_arr[this->_n] = item;
            int cur = this->_n, parent = this->__parent__(cur);
            while (cur && this->_comp(this->_arr[cur], this->_arr[parent])) {
                this->__swap__(cur, parent);
                cur = parent;
                parent = this->__parent__(cur);
            }
            ++(this->_n);
            return *this;
        }
        value_tp extract() {
            value_tp val = this->_arr[0];
            this->__swap__(0, --(this->_n));
            this->__heapify__(this->_arr, this->_n, 0);
            return val;
        }
        ~Heap() {
            delete[] this->_arr;
            this->_arr = {};
        }

    private:
        pointer _arr;
        int _n;
        int _size;
        comp _comp;

        void __expand__() {
            pointer new_arr = new value_tp[this->_size * 2];
            pointer new_iter = new_arr, arr = this->_arr, end = (arr + this->_n);
            for (; arr != end; ++arr, ++new_iter)
                *new_iter = *arr;
            delete[] this->_arr;
            this->_arr = new_arr;
        }
        void __heapify__(pointer arr, int n, int root) {
            int l = (2*root + 1), r = l + 1;
            int largest = root;
            if ((l < n) && this->_comp(arr[l], arr[largest]))
                largest = l;
            if ((r < n) && this->_comp(arr[r], arr[largest]))
                largest = r;
            if (root != largest) {
                this->__swap__(root, largest);
                __heapify__(arr, n, largest);
            }
        }
        void __swap__(int i, int j) {
            value_tp tmp = this->_arr[i];
            this->_arr[i] = this->_arr[j];
            this->_arr[j] = tmp;
        }
        static int __parent__(int i) {
            return (i & 1) ? (i / 2) : (i / 2 - 1);
        }
};
namespace _heap_help {
    constexpr int MIN{0};
    constexpr int MAX{1};
    int l, r, max_priority;

    typedef int heap_type;
    
    template<typename T>
    using comp_tp = bool (*)(const T&, const T&);
    
    template<typename T>
    void swap(T* arr, int i, int j) {
        T val = arr[i];
        arr[i] = arr[j];
        arr[j] = val;
    }

    template<typename T>
    bool _less(const T& x, const T& y) {
        return (x < y);
    }
    
    template<typename T>
    bool _greater(const T& x, const T& y) {
        return (x > y);
    }

    template<typename T>
    void _heapify(T* arr, int n, int root, comp_tp<T> f) {
        l = (2 * root + 1);
        r = l + 1;
        int max_priority = root;
        if ((l < n) && f(arr[l], arr[max_priority]))
            max_priority = l;
        if ((r < n) && f(arr[r], arr[max_priority]))
            max_priority = r;
        if (max_priority != root) {
            _heap_help::swap(arr, root, max_priority);
            _heapify(arr, n, max_priority, f);
        }
    }

    template<typename T>
    void heapify(T* arr, int n, int root, heap_type flag) {
        if (flag == MAX)
            _heapify(arr, n, root, _greater);
        else if (flag == MIN)
            _heapify(arr, n, root, _less);
    }

    template<typename T>
    void make_heap(T* arr, int n, heap_type flag) {
        comp_tp<T> f;
        if (flag == MIN)
            f = _less;
        else if (flag == MAX)
            f = _greater;
        else
            return;
        for (int i = (n/2 - 1); (i >= 0); --i)
            _heapify(arr, n, i, f);
    }
}
namespace MaxHeap {
    using namespace _heap_help;
    
    template<typename T>
    void make_heap(T* arr, int n) {
        _heap_help::make_heap(arr, n, MAX);
    }

    template<typename T>
    void sort(T* arr, int n) {
        int i{}, size{n};
        make_heap(arr, n);
        for (; i < size; ++i) {
            swap(arr, 0, --n);
            heapify(arr, n, 0, MAX);
        }
    }
}

namespace MinHeap {
    using namespace _heap_help;

    template<typename T>
    void make_heap(T* arr, int n) {
        _heap_help::make_heap(arr, n, MIN);
    }

    template<typename T>
    void sort(T* arr, int n) {
        int i{}, size{n};
        make_heap(arr, n);
        for (; i < size; ++i) {
            swap(arr, 0, --n);
            heapify(arr, n, 0, MIN);
        }
    }
}

bool l(int x, int y) { return (x < y); }
bool g(int x, int y) { return (x > y); }
typedef bool(*comp_fn)(int, int);

int main(void)
{
    int arr[] = {21, 45, 87, 69, 16, 34, 77, 30, 78, 12, 49, 3};
    Heap<int, comp_fn> H(g);
    for (int& i : arr)
        H.insert(i);
    while (!H.isEmpty()) {
        std::cout << H.extract() << "  ";
    }
    print();
    MaxHeap::sort(arr, std::size(arr));
    print(printer(arr));
    return 0;
}
