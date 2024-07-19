/*
 * Whenever we try to use a base class pointer storing the address of any
 * derived object to access the overloaded class methods we would like the
 * method of the derived class to be called which is not possible with static
 * binding since in the case of static binding the compiler only looks at the
 * type of the pointer to call the class method and not the type of the object
 * whose address the pointer contains.
 * 
 * To get around this problem, we need dynamic binding in C++. We just need to
 * prefix the methods which we want to dynamically resolved with the keyword
 * 'virtual' and the methods will be resolved at runtime depending upon the
 * type of the object that the base pointer is pointing to.
 * Same applies in case of references as well.
 * 
 * When we mark functions as virtual we make it clear that we want dynamic
 * binding and that the function call should be resolved not by looking at the
 * pointer type but rather the type of the object whose address the pointer
 * stores.
 * 
 * Only the functions marked as virtual are the ones we have access to using
 * polymorphism of the base pointer. We do not have access to non virtual
 * functions.
 * 
 * A virtual function is a member function in the base class & overridden
 * (re-defined) by its derived class(es). While declaring in the base class,
 * we use the keyword virtual to distinguish it.
 * 
 * A class that declares or inherits virtual functions is called a polymorphic
 * class.
 */
#include "shaped.h"
#include "utils.h"

void draw_all(const Shape** Shapes, size_t size);

int main(void)
{
    newline;
    Shape s{"A shape"};
    Oval o{4.7, 12.8, "Oval"};
    Circle c{23.61, "Circle"};
    sep;

    cout << "Calling methods through pointers : Dynamic Binding.\n"; sep;
    newline;

    Shape* sptr = &s;
    cout << "\tsptr = &s;\n\tsptr->draw() : "; sptr->draw(); newline;

    sptr = &o;
    cout << "\tsptr = &o;\n\tsptr->draw() : "; sptr->draw(); newline;

    sptr = &c;
    cout << "\tsptr = &c;\n\tsptr->draw() : "; sptr->draw(); newline; sep;

    // sptr->get_radius() // No access to non virtual member functions.

    cout << "Calling methods through references : Dynamic Binding.\n"; sep;
    newline;

    Shape& ref_s{s};
    Shape& ref_o{o};
    Shape& ref_c{c};
    cout << "\tShape& ref_s{s};\n\tref_s.draw() : "; ref_s.draw(); newline;
    cout << "\tShape& ref_o{o};\n\tref_o.draw() : "; ref_o.draw(); newline;
    cout << "\tShape& ref_c{c};\n\tref_c.draw() : "; ref_c.draw(); newline;
    sep; newline;
    
    const Shape* shapes[]{&s, &c, &o};
    draw_all(shapes, std::size(shapes));

    return 0;
}

void draw_all(const Shape** Shapes, size_t size){
    // The respective draw method for each object will be called
    repeat(size)
        (Shapes[i])->draw();
}