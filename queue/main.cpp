#include "queue.h"
#include <conio.h>
#include <ctime>

int main(void)
{
    std::srand(std::time(0));
    Queue q(10);
    char ch;
    int num;
    while (true)
    {
        ch = getch();
        switch(ch)
        {
            case 'e':
                q.enqueue(std::rand() % 100);
                break;
            case 'd':
                if ((num = q.dequeue()) != INT_MIN)
                    std::cout << "Dequeued : " << num << std::endl;
                break;
            case 'x':
                return 0;
        }
        std::cout << q << " size : " << q.size() << " capacity : " << q.capacity() << std::endl;
    }
    return 0;
}