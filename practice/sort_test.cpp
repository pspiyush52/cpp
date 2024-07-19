#include "carr.h"
#include "range.h"
#include "string.h"
#include "isort.h"
#include "qsort.h"
#include "hsort.h"
#include <chrono>

using namespace std::chrono;

typedef array<int> container;
typedef void (*sorter)(container&);

void insertion_sort(container& arr){ isort(arr); }
void quick_sort(container& arr){ qsort(arr); }
void heap_sort(container& arr){ hsort(arr); }

double analyze(container& arr, sorter sort_fun){
    auto start = high_resolution_clock::now();
    sort_fun(arr);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    return (1.0 * duration.count()) / 1e3;
}
const char* alg_names[] = {"insertion", "quick", "heap"};
sorter sort_funs[] = {insertion_sort, quick_sort, heap_sort};

int main(int argc, char* argv[]){
    if (argc == 3){
        string alg_opt{argv[1]}, test_size{argv[2]};
        if ((alg_opt[0] != '-') || (alg_opt.size() > 2)){
            std::cout << "Invalid option " << alg_opt << '\n';
            return 1;
        }
        size_t size{}, i{};
        try{
            size = test_size.stoull();
        }
        catch(ValueError&){
            std::cout << "Invalid value of test size\n";
            return 1;
        }
        container arr(size);  rand_range(0, INT_MAX) >> arr;
        switch (alg_opt[1]){
            case 'i':
                i = 0;
                break;
            case 'q':
                i = 1;
                break;
            case 'h':
                i = 2;
                break;
            case 'n':{
                printf("\nTime taken to sort %llu integers,\n", size);
                for (int i{1}; i < 3; ++i){
                    printf("\t%s sort = %.3fms\n", alg_names[i], analyze(arr, sort_funs[i]));
                    rand_range(0, INT_MAX) >> arr;
                }
                return 0;
            }
            default:
                printf("Invalid algorithm option\n");
                return 1;
        }
        printf("\nTime taken to sort %llu integers using %s sort = %.3fms\n", size, alg_names[i], analyze(arr, sort_funs[i]));
    }
    else if (argc == 2){
        string test_size{argv[1]};
        size_t size{};
        try{
            size = test_size.stoull();
        }
        catch(ValueError&){
            std::cout << "Invalid value of test size\n";
            return 1;
        }
        container arr(size);
        printf("\nTime taken to sort %llu integers,\n", size);
        for (int i{}; i < 3; ++i){
            rand_range(0, INT_MAX) >> arr;
            printf("\t%s sort = %.3fms\n", alg_names[i], analyze(arr, sort_funs[i]));
        }
    }
    return 0;
}