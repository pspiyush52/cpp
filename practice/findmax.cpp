#include "print.h"
#include "frand.h"

template<typename arr_tp, size_t size>
class FindMax {
    public:
        FindMax(arr_tp (&A)[size]);
        arr_tp getMax() const;
        arr_tp getNextMax() const;

    private:
        arr_tp (&arr)[size];
        arr_tp max;
        arr_tp nextMax;
};

int main(void)
{
    const int SIZE{15};
    int arr[SIZE];
    printer(rng().integers(0, 100, SIZE)) >> arr;
    FindMax M{arr};
    print("Array:", printer(arr));
    print("Max:", M.getMax(), "\nNextMax:", M.getNextMax());
    return 0;
}

template<typename arr_tp, size_t size>
FindMax<arr_tp, size>::FindMax(arr_tp (&A)[size]): arr(A) {
    this->max = A[0];
    this->nextMax = A[0];
    for (size_t i{}; i < size; ++i) {
        if (A[i] > this->max) {
            this->nextMax = this->max;
            this->max = A[i];
        }
        else if (A[i] > this->nextMax)
            this->nextMax = A[i];
    }
}

template<typename arr_tp, size_t size>
arr_tp FindMax<arr_tp, size>::getMax() const {
    return this->max;
}
template<typename arr_tp, size_t size>
arr_tp FindMax<arr_tp, size>::getNextMax() const {
    return this->nextMax;
}
