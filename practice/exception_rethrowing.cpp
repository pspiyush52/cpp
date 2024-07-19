#include "excepts_poly.h"
#include <typeinfo>

int main(void)
{
    try{
        try{
            throw CriticalError{"Undefined reference to \"main\"", __LINE__};
        }
        /*
         * The inner catch block will only deal with exceptions which are
         * warnings and if it is not a warning the exception will be rethrown
         * and will have to be caught outside of this catch block.
         */
        catch(ExceptionBase& ex){
            if (typeid(ex) == typeid(Warning))
            {
                std::cout << "Inner catch exception caught, " << ex.what() << '\n';
            }
            else
                throw;
                // throw ex;  // will cause ex to be copied, and slicing will be involved.
        }
    }
    /*
     * This catch block will catch any exceptions which are rethrown by the
     * inner catch block.
     */
    catch(ExceptionBase& ex){
        std::cout << "Outer catch exception caught, " << ex.what() << '\n';
    }
    return 0;
}