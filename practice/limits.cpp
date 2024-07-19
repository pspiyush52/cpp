#include <iostream>
#include <limits>

#define cout std::cout
#define endl std::endl
#define lim std::numeric_limits

int main(void)
{
    cout << endl << "\tsigned short is from " << lim<short>::min() << " to " << lim<short>::max() << endl;
    cout << endl << "\tunsigned short is from " << lim<unsigned short>::min() << " to " << lim<unsigned short>::max() << endl;
    cout << endl << "\tsigned int is from " << lim<int>::min() << " to " << lim<int>::max() << endl;
    cout << endl << "\tunsigned int is from " << lim<unsigned int>::min() << " to " << lim<unsigned int>::max() << endl;
    cout << endl << "\tsigned long is from " << lim<long>::min() << " to " << lim<long>::max() << endl;
    cout << endl << "\tunsigned long is from " << lim<unsigned long>::min() << " to " << lim<unsigned long>::max() << endl;
    cout << endl << "\tsigned long long is from " << lim<long long>::min() << " to " << lim<long long>::max() << endl;
    cout << endl << "\tunsigned long long is from " << lim<unsigned long long>::min() << " to " << lim<unsigned long long>::max() << endl;
    cout << endl << "\tfloat is from " << lim<float>::lowest() << " to " << lim<float>::max() << " with min : " << lim<float>::min() << endl;
    cout << endl << "\tdouble is from " << lim<double>::lowest();
        cout << " to " << lim<double>::max() << " with min : " << lim<double>::min() << endl;
    cout << endl << "\tlong double is from " << lim<long double>::lowest();
        cout << " to " << lim<long double>::max() << " with min : " << lim<long double>::min() << endl;
    return 0;
}