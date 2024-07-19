#include "lists.h"
#include "deque.h"
#include "avl.h"
#include "print.h"
#include "utils.h"
#include "defs.h"
#include "hsort.h"
#include "range.h"

typedef arr::List<int> con1;
typedef deque<int>     con2;
typedef Set<int>       con3;

int main(int argc, char* argv[])
{
    const int SIZE{1000000}, from{}, to{100000000};
    rng r;
    con1 li{};
    con2 dq{};
    con3 s{};
    auto time_l = timeit([&](con1& c){
        repeats(SIZE)  c.append(r.randint(from, to));
        hsort(c);
    }, li);
    auto time_d = timeit([&](con2& c){
        repeats(SIZE/2)  c.push_back(r.randint(from, to));
        repeats(SIZE/2)  c.push_front(r.randint(from, to));
        hsort(c);
    }, dq);
    auto time_s = timeit([&](con3& c){
        repeats(SIZE)  c.insert(r.randint(from, to));
    }, s);
    print("Time taken for the list:", time_l/1e3);
    print("Time taken for deque:", time_d/1e3);
    print("Time taken for set:", time_s/1e3);
    return 0;
}