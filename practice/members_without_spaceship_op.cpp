#include <iostream>

class num {
    public:
        num() = default;
        num(int n) : data(n){}
        int get() const { return data; }
        bool operator==(const num& rhs) const {
            return (data == rhs.data);
        }
        bool operator<(const num& rhs) const {
            return (data < rhs.data);
        }
    private:
        int data{};
};

class item {
    public:
        item() = default;
        item(int X, int Y, int Z) : a(X), b(Y), x(Z){}
        item(int x, int y) : a(x), b(y){}
        item(int a_b) : item(a_b, a_b, a_b){}
        /*
            // auto operator<=>(const item& rhs) const = default;

            When we try to define the three way comparison operator for this
            class the compiler checks if it can perform comparisons on every
            member variable or not. Since we haven't defined any comparison
            operators for the num class the compiler sees that it cannot
            perform member-wise comparison on all members of this class and so
            the function for operator '<=>' gets deleted and we are unable to
            perform logical comparisons on objects of this class.

            But if we define the '==' and '<' operators for the num class then
            we might expect that the compiler may deduce the rest of the
            operators from these two like it happens with namespace rel_ops.

            // auto operator<=>(const item& rhs) const = default;

            This will still not work even after we define the '==' and '<'
            operators for the class num because the num class doesn't have the
            concept of three way comparisons and so if we keep the return type
            of the function as auto the compiler will not be able to deduce if
            the return will be strong_ordering, weak_ordering or
            partial_ordering.
            So we have to help the compiler and specify the type of ordering
            ourselves and then it will work as expected.
        */
        std::strong_ordering operator<=>(const item& rhs) const = default;
        friend std::ostream& operator<<(std::ostream& output, const item& n){
            output << "item[" << n.a << ", " << n.b << ", " << n.x.get() << ']';
            return output;
        }
    private:
        int a{};
        int b{};
        num x;
};

int main(void)
{
    const item x{0, 2, 1}, y{1, 0, 8};
    std::cout << "x: " << x << ", y: " << y << '\n';
    std::cout << std::boolalpha;
    std::cout << "x < y : " << (x < y) << '\n';

    return 0;
}