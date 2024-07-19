/*
 * Class destructors by default have noexcept specifier attached to them.
 * So if we try to throw an exception out of a class destructor, the
 * program will terminate immediately.
 * 
 * However, if we want to force the destructor to throw an exception then
 * we can use the noexcept(false) specifier like,
 *                  ~class_name() noexcept(false){
 *                  }
 */
#include "utils.h"
class Item{
    public:
        Item() = default;
        /*
         * Using noexcept(false) allows this destructor to throw
         * exceptions.
         */
        // ~Item() noexcept(false){
        ~Item(){
            try{
                throw 1;
            }
            /*
             * This catch clause will not catch the exception since it is
             * of type int but the catch clause parameter is of type
             * double.
             */
            catch(double ex){
                std::cout << "Caught exception in the destructor of Item.\n";
            }
        }
        void fun(){
            throw 1;
        }
};

int main(void)
{
    fmt::start();
    std::cout << "Starting main...\n";
    try{
        {
            Item i;
            /*
             * If we call the fun() method then since it is not marked
             * noexcept, it will be allowed to throw the exception and we
             * will be able to catch the exception in the catch block
             * below.
             */
            try{
                i.fun();
            }
            // The exception thrown by fun() will be caught here.
            catch(int ex){
                std::cout << "Exception caught in the inner block.\n";
            }
            /*
             * But if we try to throw an exception in the destructor and
             * the object goes out of scope since the destructor is
             * marked noexcept it will not be allowed to throw an
             * exception and the program will immediately terminate.
             */
        }
        /*
         * After this block ends the object i will go out of scope and
         * the destructor will be called which is trying to throw an
         * exception but since destructors are marked noexcept
         * automatically, it will not be allowed to throw the exception
         * and the program will terminate immediately.
         */
    }
    catch(...){
        std::cout << "Exception occurred.\n";
    }
    std::cout << "main finished...\n";
    fmt::end();
    return 0;
}