#include <iostream>
#include <string.h>

struct A{
    public:
        A() = default;
        char ch;
        int x;
        friend std::ostream& operator<<(std::ostream& output, const A& obj){
            output << "(ch: " << obj.ch << ", x: " << obj.x << ", ll: " << obj.ll << ')';
            return output;
        }
        void display(){
            std::cout << "(ch: " << ch << ", x: " << x << ", ll: " << ll << ')';
        }
        void display_layout(){
            std::cout << "Offsets of members:\n";
            std::cout << "\tchar ch: " << (&ch - (char*)this) << '\n';
            std::cout << "\tint x: " << ((char*)&x - (char*)this) << '\n';
            std::cout << "\tlong long ll: " << ((char*)&ll - (char*)this) << '\n';
        }
        // Since A is a Standard layout type so the objects are memcopyable.
        A(const A& src){
            memcpy(this, &src, sizeof(A));
        }
    // private:
        long long ll;
};

int main(void)
{
    A x;
    x.ch = '^'; x.x = 4654982; x.ll = 78113226654;
    std::cout << std::boolalpha;
    std::cout << std::is_trivial_v<A> << '\n';
    std::cout << std::is_standard_layout_v<A> << '\n';
    std::cout << (std::is_trivial_v<A> && std::is_standard_layout_v<A>) << '\n';
    std::cout << x << '\n';
    A copy_x{x};
    std::cout << copy_x << '\n';
    return 0;
}