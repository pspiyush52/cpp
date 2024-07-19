#include <iostream>

using namespace std;
int range(int a, int b)
{
    static long long int i;
    static int state = 0;
    switch (state)
    {
        case 0:{
            state = 1;
        }
        
        for (i = a; i < b; i++)
        {
            return i;
            case 1:
                continue;
        }
    }

    state = 0;
    return 0;
}

int main()
{
    int i;
    for (; i = range(1, 5);)
        cout << i << ' ';
    return 0;
}