/*
 * When we have a hierarchy of exception classes then any exception of derived
 * exception class will match with the catch clause which has a base exception
 * type as parameter.
 * 
 * In the Exception class hierarchy given below,
 * 
 *                              ExceptionBase
 *                                    |
 *                                    |
 *                                 Warning
 *                                    |
 *                                    |
 *                               Small Error
 *                                    |
 *                                    |
 *                              Critical Error
 * 
 * Any exception of the derived types can be caught by catch clauses having a
 * base exception type as parameter.
 * 
 * The base class however, has to be a public base class.
 * 
 * In other words, if we throw an Exception of type E then it will match
 * against the types of formal parameters T of each catch clause after the try
 * block in the order in which they are listed. The exception is a match if T
 * is an unambiguous public base class of E or T is a reference to an
 * unambiguous public base class of E.
 */
#include <iostream>
#include "excepts.h"

int main(void)
{
    /*
     * Since the base exception type will catch any of the derived type
     * exceptions we should list the catch clauses in such a way that the
     * clause with the most derived exception type as its parameter is listed
     * first and then the other clauses with decreasing specificity in their
     * parameter types.
     * 
     * In other words, we move from the most derived towards the base and not
     * the other way around or else all exceptions will be caught in the base
     * clause and no other clause will be triggered even for specific
     * exceptions.
     */
    try{
        throw CriticalError("Main cannot be executed.");
    }
    catch(CriticalError& ex){
        std::cout << "CriticalError: " << ex.what() << '\n';
    }
    catch(SmallError& ex){
        std::cout << "SmallError: " << ex.what() << '\n';
    }
    catch(Warning& ex){
        std::cout << "Warning: " << ex.what() << '\n';
    }
    catch(ExceptionBase& ex){
        std::cout << "Exception: " << ex.what() << '\n';
    }

    return 0;
}