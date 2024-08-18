#include "deque.h"
#include "..\practice\stream_insertable.h"
#include "..\practice\defs.h"
#include "..\practice\print.h"
#include "..\practice\base_derived.h"
#include <vector>

int main(void)
{
    Derived x{44};
    deque<Derived> d;
    print();
    print(x.isValid());
    d.push_back(static_cast<Derived&&>(x));
    // d.push_back(Derived(10));
    print(x.isValid());
    print(d);
    print();
    return 0;
}
