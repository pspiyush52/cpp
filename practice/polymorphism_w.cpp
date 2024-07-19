/*
 * So why do we need polymorphism? Suppose that we have a class heirarchy
 * where Shape is the base class, Oval derives from Shape and Circle derives
 * from Oval.
 * Suppose each class has its own draw() method using which it can be drawn on
 * the screen. If we wish to define separate functions to draw each of them
 * then we would have to define three separate functions taking either a Shape
 * or a Oval or a Circle as a parameter like,
 * 
 *      void draw_circle(const Circle& circle){
 *          circle.draw();
 *      }
 * 
 *      void draw_oval(const Oval& oval){
 *          oval.draw();
 *      }
 * 
 * Now as the number of shapes in our program grows, so will the number of
 * functions needed which can be quite cumbersome to write.
 * 
 * Take another case where we have to store objects of different shape types
 * in one array/collection. Without polymorphism we would have to store all
 * the objects of one type in one array and so if we have a lot of shape
 * types, we will have to create and maintain lots of separate arrays.
 * 
 *      Circle circle_array[]{c1, c2, c3, c4, c5};
 *      Oval oval_array[]{o1, o2, o3, o4, o5, o6, o7};
 *          .
 *          .
 *          .
 * 
 * Creating and using so many different arrays in our program can easily get
 * mind boggling so we would like to avoid it if possible.
 * 
 * So, for the first problem what we would like to have is a single function
 * which takes a base class reference (or pointer) as a parameter and
 * depending on the type of object we call it with, it uses the draw method of
 * that particular class to draw that object on the screen
 * 
 *      void draw_shape(Shape* sptr){
 *          sptr->draw();  // calls the right method for the object passed in
 *      }
 * 
 *      void draw_shape(const Shape& shape){
 *          shape.draw();  // calls the right method for the object passed in
 *      }
 * 
 * Similarly for storing objects of different types in one collection we would
 * like to declare one single array of type pointer to base and then store the
 * pointers to the different objects in the array like,
 * 
 *      Shape* shapes[]{&c1, &c2, &o1, &c3, &o2};
 * 
 * and we would like to access the draw() method of the respective class when
 * we get the pointer to a particular shape using the array index notation
 * like,
 * 
 *      (shapes[1])->draw();  // calls the Circle::draw() method since object
 *                            // at index 1 is of Circle type.
 * 
 * However, these features can be accessed using dynamic binding but the
 * default behavior in C++ is static binding.
 */
#include "shape.h"

int main(void)
{
    Shape s{"shape"};
    Oval o{12, 15, "oval"};
    Circle c{4.8, "circle"};

    Shape* shapes[]{&s, &o, &c};

    // std::cout << "Total number of shapes: " << Shape::shape_count() << '\n';
    std::cout << "Total number of shapes: " << c.shape_count() << '\n';

    return 0;
}