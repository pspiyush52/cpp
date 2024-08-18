#include <string>
#include "print.h"
#include "frand.h"
#include "plist.h"

int main(void)
{
    auto det = [] <typename T> (const PList<T>& p) {
        print(p);
        print("Size:", p.size());
        print("Capacity:", p.capacity());
    };
    rng r;

    PList<std::string> names;
    for (int i{}; i < 7; ++i) {
        std::string s;
        int start[] = {'a', 'A'};
        int j{}, upto{r.randint(3, 20)};
        for (; j < upto; ++j) {
            s.push_back(start[r.randint(2)] + r.randint(26));
        }
        names.emplace(static_cast<std::string&&>(s));
    }
    det(names);
    auto s = std::move(names[1]);
    det(names);
    names[1] = "\"String at index 1 is restored\"";
    // names.emplaceAt(1, "\"What is this?\"");
    det(names);
    return 0;
}
