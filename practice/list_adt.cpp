#include "print.h"

template<typename T>
class List {
    public:
        virtual List& append(const T& item) = 0;
        virtual List& append(T&& item) = 0;
        virtual T pop() = 0;
        virtual size_t size() const = 0;
        virtual bool isEmpty() const = 0;
};

template<typename T>
class DList : public List<T> {
    static const size_t DEFAULT_SIZE{16};
    public:
        DList(size_t size) {
            size = (size < DEFAULT_SIZE) ? DEFAULT_SIZE : size;
            this->_arr = new T[size];
            this->_size = size;
            this->_cur = {};
        }
        DList(): DList(DEFAULT_SIZE) {}

        List<T>& append(const T& item) {
            if (this->isFull())
                this->__expand__();
            this->_arr[(this->_cur)++] = item;
            return *this;
        }
        List<T>& append(T&& item) {
            if (this->isFull())
                this->__expand__();
            this->_arr[(this->_cur)++] = item;
            return *this;
        }
        T pop() {
            if (this->isEmpty())
                throw std::range_error("Exception: List empty");
            return this->_arr[--(this->_cur)];
        }
        size_t size() const {
            return this->_size;
        }
        bool isEmpty() const {
            return (this->_cur == 0);
        }
        ~DList() {
            delete[] this->_arr;
            this->_arr = {};
        }
        template<typename U>
        friend std::ostream& operator<<(std::ostream& out, const DList<U>& list) {
            out << '[';
            if (!list.isEmpty()) {
                size_t i{}, upto{list._cur - 1};
                for (; i < upto; ++i)
                    out << list._arr[i] << ", ";
                out << list._arr[i];
            }
            out << ']';
            return out;
        }
    
    private:
        T* _arr{};
        size_t _size{};
        size_t _cur{};

        bool isFull() {
            return (this->_cur == this->_size);
        }
        void __expand__() {
            T* new_arr = new T[2 * this->_size];
            for (size_t i{}; i < this->_cur; ++i)
                new_arr[i] = this->_arr[i];
            delete[] this->_arr;
            this->_arr = new_arr;
            this->_size *= 2;
        }
};

int main(void)
{
    DList<int> nums;
    nums.append(12).append(14).append(13);
    print(nums);
    while (!nums.isEmpty())
        print(nums.pop());
    print(nums);
    return 0;
}
