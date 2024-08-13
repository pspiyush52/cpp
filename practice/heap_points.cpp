#include "print.h"
#include "points.h"
#include "heap.h"

int main(void)
{
    Point Points[] = {
        {0, 1}, {1.5, 2.3}, {1, 3}, {4.1, 1.7}, {0.732, 0.515}
    };
    Point X{4, 5};
    print(printer(Points), '\n');

    Heap minHeap(Points, Less(), [&](Point& p){
        return p.distance(X);
    });
    
    while (!minHeap.isEmpty()) {
        Point p = minHeap.extract();
        print(p);
        print("Distance from", X, "=", p.distance(X), '\n');
    }
    
    return 0;
}
