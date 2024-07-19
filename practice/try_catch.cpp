#include <iostream>

class item{
    public:
        item(){ std::cout << "item created.\n"; }
        ~item(){ std::cout << "item destroyed.\n"; }
};

int main(void)
{
    int num;
    std::cout << "Enter number: ";
    try{
        std::cin >> num;
        /*
         * When an exception is thrown the control immediately exits the try
         * block and goes to the catch block.
         * Any local variables declared in the try block are destroyed when
         * the control goes out of the try block so if any memory is allocated
         * within a try block, it will be leaked if we are not careful.
         * 
         * Any object which is thrown must be copyable i.e., must contain a
         * copy constructor in its class definition because the thrown object
         * is copied to the parameter of the catch block.
         * 
         * The type of the thrown exception has to exactly match with the type
         * in the catch statement. No type conversions are done.
         */
        item i;  // will be immediately destroyed upon encountering the throw
                 // statement
        if (num < 0 || num > 9)
            throw "Incorrect";
            // throw 0;
        
        std::cout << num << " is " << ((num % 2) ? "odd" : "even") << '\n';
    }
    catch(const char* ex){
        std::cout << ex << '\n';
        return 1;
    }
    catch(int ex){
        std::cout << ex << '\n';
        return 1;
    }
    
    return 0;
}