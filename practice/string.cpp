#include "string.h"
#include "frand.h"
#include "ordered_map.h"

int main(void)
{
    OrderedSMap<String, deque<String>> m{
        {"two", {"this", "is", "a", "List"}},
        {"pees", String::split("piyush pranjai pratibha prasham pratima")},
        {"four", String::split("this is a list")},
        {"five", String::split("this is a list")}
    };
    m.insert("first", {"what", "is", "happening"});
    print(m);
    print();
    print(m["pees"]);
    return 0;
}
