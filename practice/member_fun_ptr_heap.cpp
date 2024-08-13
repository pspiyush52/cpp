#include "print.h"
#include "tuples.h"
#include "frand.h"

template<typename Container, typename Projection>
class Heap {
    public:
        Heap(Container& container, Projection projection);
        auto extract() {
            auto val{this->con[0]};
            swap(0, this->n - 1);
            --(this->n);
            this->Heapify(0);
            return val;
        }
        bool isEmpty();
        
    private:
        Container& con;
        int n{};
        Projection proj;

        void swap(int i, int j);
        void Heapify(int r);
};
std::ostream& operator<<(std::ostream& out, const Pair<int, int>& P);

int main(void)
{
    Pair<int, int> A[10];
    rng r;
    for (auto& p : A) {
        p.setFirst(r.randint(-20, 100));
        p.setSecond(r.randint(-20, 100));
    }
    print("\nArray of tuples:", printer(A));
    Heap H(A, Pair<int, int>::getSecond);
    print("\nThe tuples in a non-decreasing order by the second item");
    std::cout << '\t';
    while (!H.isEmpty())
        std::cout << H.extract() << "  ";
    print("\n");
    return 0;
}

template<typename Container, typename Projection>
Heap<Container, Projection>::Heap(Container& container, Projection projection):
con{container}, n(std::size(container)), proj{projection} {
    for (int i{n/2 - 1}; i >= 0; --i)
        this->Heapify(i);
}

template<typename Container, typename Projection>
bool Heap<Container, Projection>::isEmpty() {
    return (!(this->n));
}

template<typename Container, typename Projection>
void Heap<Container, Projection>::swap(int i, int j) {
    auto tmp = con[i];
    con[i] = con[j];
    con[j] = tmp;
}

template<typename Container, typename Projection>
void Heap<Container, Projection>::Heapify(int r) {
    int left{}, right{}, minIndex{};
    while (r <= n/2) {
        minIndex = r;
        left = 2*r + 1;
        right = left + 1;
        if (left < n && (con[left].*proj)() < (con[minIndex].*proj)())
            minIndex = left;
        if (right < n && (con[right].*proj)() < (con[minIndex].*proj)())
            minIndex = right;
        if (minIndex == r)
            break;
        else
            swap(r, minIndex);
        r = minIndex;
    }
}

std::ostream& operator<<(std::ostream& out, const Pair<int, int>& P) {
    out << "(" << P.getFirst() << ", " << P.getSecond() << ")";
    return out;
}
