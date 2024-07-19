/*
 * Template instance for a given type is created only once and then
 * reused if need be.
 * 
 * Only the methods that are used in the program are instantiated.
 * 
 * Methods of template classes are marked inline by default.
 * 
 * A function defined entirely inside a class/struct/union definition,
 * whether it's a member function or a non-member friend function, is
 * implicitly an inline function.
 * 
 * We can have non type template parameters as well but for each separate
 * non type template parameters a separate class instance will be
 * generated.
 * Ex:
 *      template<typename T, T threshold>
 *      class MyClass{
 *          ...
 *      };
 * 
 * MyClass<int, 10> obj1;    // Will generate a template instance
 * MyClass<int, 11> obj2;    // Will generate another template instance
 * MyClass<int, 20> obj3;    // Yet another template instance generated
 * 
 * It results in unnecessary template instantiations.
 */
#include <iostream>
#include "stream_insertable.h"

template<typename T, typename U>
class Map : public StreamInsertable{
    public:
        Map(const T& key, const U& value) : _key(key), _value(value){}
        void stream_insert(std::ostream& output) const override{
            output << "{key: " << _key << ", value: " << _value << '}';
        }

    private:
        T _key;
        U _value;
};

template<typename T, T default_value>
struct p{
    T x{default_value};
    T y{default_value};
};

int main()
{
    const char* name{"Piyush"};
    Map m{name, 27};
    std::cout << m << '\n';

    p<int, 32> obj;
    return 0;
}