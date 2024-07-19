#include <iostream>

template<typename T>
void _comb(T* arr, size_t size, int from){
    if (from < size){
        for (int i{from + 1}; i < size; ++i)
            std::cout << '{' << arr[from] << " : " << arr[i] << "} ";
        _comb(arr, size, from + 1);
    }
}

template<typename _arr_tp, size_t size>
void comb(_arr_tp (&arr)[size]){
    _comb(arr, size, 0);
}

int main(int argc, char* argv[])
{
    int arr[] = {1, 2, 3, 4, 5, 6};
    comb(arr);
    return 0;
}