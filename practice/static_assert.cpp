#include "print.h"
#include "stream_insertable.h"

template<typename T, size_t size>
class vector : public StreamInsertable {
    static_assert(
        size > 3, "The size of the vector cannot be less than 4\n"
    );
    public:
        vector() = default;
        T& operator[](int i) {
            return this->A[i];
        }
        const T& operator[](int i) const {
            return this->A[i];
        }
        constexpr size_t len() const {
            return size;
        }
    private:
        T A[size];
        void stream_insert(std::ostream& out) const {
            size_t i{};
            out << "[";
            for (; i < size - 1; ++i)
                out << this->A[i] << ", ";
            out << this->A[i] << "]";
        }
};

template<typename T>
void fun(T& A) {
    static_assert(
        A.len() > 8, "Vector of size less than 8 not allowed.\n"
    );
    std::cout << "fun(T&)\n";
}

int main(void)
{
    constexpr int n{7};
    vector<int, n> arr;
    for (int i{}; i < n; ++i)
        arr[i] = i;
    print(arr);
    print(arr.len());
    return 0;
}
