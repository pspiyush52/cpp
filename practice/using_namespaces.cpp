#include <iostream>
#include <string>

int main(void)
{
    /*
        using can be used to bring in some names from the namespace or bring
        in all the names from the entire namespace.

        using std::cout; // brings in cout from the std namespace into the
        current namespace.

        using namespace std; // brings in the entire std namespace into the
        current namespace.
    */
    using std::cout, std::endl;
    cout << "Hello there" << endl;

    using namespace std;  // brings the entire std namespace
    string name{"some_name"};
    cout << "Name : " << name << endl;

    return 0;
}