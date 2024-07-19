#include <iostream>
#include <initializer_list>

class myclass {
    public:
        myclass(std::initializer_list<int> args);
        ~myclass();
    private:
        int x;
        int y;
        int z;
        friend std::ostream& operator<<(std::ostream& output, myclass& obj);
};

int main(void)
{
    myclass obj1{45};
    myclass obj2{1, 0, 4};
    std::cout << obj2 << '\n';
    return 0;
}

myclass::myclass(std::initializer_list<int> args)
{
    std::cout << "Constructor called for object at " << this << '\n';
    if (args.size() != 3)
    {
        std::cerr << "Invalid number of arguments.\n";
        return;
    }
    // begin() returns a pointer to the first element of the initializer list
    const int* first = args.begin();
    x = *(first++);
    y = *(first++);
    z = *first;

    // end() returns a pointer to an element past the last element of the
    // initializer list
}
myclass::~myclass(){
    std::cout << "Destructor called for object at " << this << '\n';
}

std::ostream& operator<<(std::ostream& output, myclass& obj)
{
    output << "myclass object at " << &obj << " <x: " << obj.x
    << ", y: " << obj.y << ", z: " << obj.z << ">";
    return output;
}