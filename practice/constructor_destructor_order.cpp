#include <iostream>

class MyClass {
    public:
        MyClass(const char* name);
        ~MyClass();
    private:
        const char* m_name;
};

int main(void)
{
    MyClass obj1("Object 1");
    MyClass obj2("Object 2");
    MyClass obj3("Object 3");
    MyClass obj4("Object 4");
    MyClass obj5("Object 5");

    // Constructors are called in the order of object creation but the
    // Destructors are called in the reverse order i.e., the object created
    // last will be destroyed first.
    
    return 0;
}

MyClass::MyClass(const char* name)
{
    m_name = name;
    std::cout << "Constructor called for " << m_name << std::endl;
}

MyClass::~MyClass()
{
    std::cout << "Destructor called for " << m_name << std::endl;
}