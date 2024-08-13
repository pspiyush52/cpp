#include "print.h"

void printCommas(unsigned long long num, char sep = ',') {
    if (num < 1000) {
        std::cout << num;
    }
    else {
        printCommas(num / 1000, sep);
        std::cout << sep << (num % 1000);
    }
}
class bin {
    public:
        bin(long long unsigned int num): n{num} {}
        friend std::ostream& operator<<(std::ostream& out, const bin& b) {
            b.streamInsert(out);
            return out;
        }
    private:
        long long unsigned int n{};
        static void _hlp_(std::ostream& out, long long unsigned int num) {
            if (num) {
                _hlp_(out, num >> 1);
                out << (num & 1);
            }
        }
        void streamInsert(std::ostream& out) const {
            if (this->n)
                _hlp_(out, this->n);
            else
                out << '0';
        }
};
void _pb_helper_(long long unsigned int num) {
    if (num) {
        _pb_helper_(num >> 1);
        std::cout << (num & 1);
    }
}
void printBinary(long long unsigned int num) {
    if (num)
        _pb_helper_(num);
    else
        std::cout << '0';
}

int main(int argc, const char* argv[])
{
    // printCommas(1123435643);
    printBinary(INT_MAX);
    print();
    printBinary(UINT_MAX);
    print();
    printBinary(0);
    std::cout << bin(15) << '\n';
    return 0;
}
