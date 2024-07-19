#include "arrs.h"
#include "stream_insertable.h"
#include <cstring>

class str : public arr::Array<char>, public StreamInsertable{
    public:
        using arr::Array<char>::Array;
        str(){ arr = nullptr; arr_size = 0; }
        str(const char* s) : Array<char>(std::strlen(s)){
            char* array = arr;
            while((*(array++)) = (*(s++)));
        }
        void stream_insert(std::ostream& output) const override {
            if (!arr_size)
                return;
            for (size_t i{}; i < arr_size; i++)
                output << arr[i];
        }
        str& operator=(const str& rhs){
            delete[] arr;
            arr = new char[rhs.arr_size];
            arr_size = rhs.arr_size;
            for (size_t i{}; i < arr_size; i++)
                arr[i] = rhs.arr[i];
            return *this;
        }
};

int main(void)
{
    str name{"Niharika"};
    std::cout << name << '\n';
    str nickname;
    nickname = name;
    std::cout << nickname << '\n';
    return 0;
}