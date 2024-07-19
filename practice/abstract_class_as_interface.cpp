/*
 * An abstract class with only pure virtual functions and no member variables
 * can be used to mode an interface in Object Oriented Programming.
 * An interface is a specification of something that will be fully implemented
 * in a derived class, but the specification itself resides in the base class.
 */
#include "stream_insertable.h"
class point : public StreamInsertable{
    public:
        point(double X, double Y) : x(X), y(Y){}
        void stream_insert(std::ostream& output) const override {
            output << "Point(x: " << x << ", y: " << y << ')';
        }

    private:
        double x;
        double y;
};

int main(void)
{
    point p{3, 5.4};
    std::cout << p << '\n';
    return 0;
}