#include <iostream>
#include <stdlib.h>
#include "qsort.h"
#include "print.h"
template<typename T, typename U=T>
class pair{
    public:
        pair() = default;
        pair(const T& first, const U& second):
            __first(first), __second(second){}
        const T& first() const{ return this->__first; }
        const U& second() const{ return this->__second; }
    private:
        T __first;
        U __second;
};
template<typename T, typename U>
std::ostream& operator<<(std::ostream& output, const pair<T, U>& p){
    output.put('(');
    output << p.first() << ", " << p.second();
    output.put(')');
    return output;
}

int main(void)
{
    pair<int> pairs[] = {
        {21, 15}, {10, 14}, {17, 4}, {25, 31}
    };
    std::cout << printer(pairs) << '\n';
    qsort(pairs, less(), [](pair<int>& p){ return p.second(); });
    std::cout << printer(pairs) << '\n';
    return 0;
}