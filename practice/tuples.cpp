#include "utils.h"
#include "tuples.h"
#include "points.h"
#include "plist.h"

Pair<int, Pair<double, double>> getPoint() {
    Pair<int, Pair<double, double>> p;
    p.emplaceFirst(1);
    p.emplaceSecond();
    p.getSecond().emplaceFirst(1.982);
    p.getSecond().emplaceSecond(15.012);
    return p;
}

int main(void)
{
    Pair<Point> t;
    t.emplaceFirst(1.0, 2.0);
    t.emplaceSecond(3.0, 4.0);
    print("Pair of points:", t);
    print("Distance of first point from origin:", t.getFirst().length());
    print("Distance of second point from origin:", t.getSecond().length());

    PList<Triple<std::string, std::string, int>> names;
    const char* firsts[] = {"Piyush", "Niharika"};
    const char* seconds[] = {"Singh", "Joshi"};
    names.emplace().emplace();
    for (int i{}; i < names.size(); ++i) {
        names[i].emplaceFirst(firsts[i]);
        names[i].emplaceSecond(seconds[i]);
        names[i].emplaceThird(25);
    }
    print(names);
    auto&& p = getPoint();
    print(p);
    print(p.getSecond());
    return 0;
}
