#include "deque.h"
#include "..\practice\stream_insertable.h"
#include "..\practice\defs.h"
#include "..\practice\print.h"

class Pair : public StreamInsertable {
    public:
        Pair() = default;
        Pair(int x, int y): m_x{x}, m_y{y} {}
        int m_x{};
        int m_y{};
        void stream_insert(std::ostream& out) const {
            out << "(x: " << this->m_x << ", y: " << this->m_y << ")";
        }
};

int main(void)
{
    // deque<int> nums{43, 17, 8, 12, 78};
    // deque<short> points{0, 1, 3, 18, 9, 11};
    // print(nums, points);
    // nums.push_front(points);
    // print(nums);
    // for (auto& x : nums(3, 10))
    //     std::cout << x << "  ";
    // print();
    Pair x, y{2, 3}, z{y};
    auto det = [](std::initializer_list<Pair> args) {
        for (auto& arg : args)
            print(arg);
    };
    det({x, y, z});
    return 0;
}
