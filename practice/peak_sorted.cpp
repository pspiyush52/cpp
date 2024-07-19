#include "carr.h"
#include "frand.h"
#include "isort.h"

array<int> make_array_with_peak();
int find_peak(array<int>&);
int find_peak(array<int>&, int, int);

int main(void)
{
    array<int> arr1 = make_array_with_peak();
    rng r;
    auto arr2 = r.rnums<array<int>>(0, 100, 20);
    // array<int> arr2{50, 17, 84, 37, 30, 40, 15, 81, 41, 22, 41, 14, 72, 68, 53, 91, 87, 53, 85, 6};
    std::cout << "The array with a single peak: " << arr1 << '\n';
    std::cout << "The peak occurs at index: " << find_peak(arr1) << '\n';
    std::cout << "\nThe array with several peaks: " << arr2 << '\n';
    std::cout << "A peak occurs at index: " << find_peak(arr2) << '\n';
    std::cout << "A peak occurs at index: " << find_peak(arr2, 0, arr2.size() - 1) << '\n';
    return 0;
}

array<int> make_array_with_peak(){
    rng r;
    int first_size{r.randint(1, 19)}, i{};
    auto first = isort(r.rnums<array<int>>(0, 100, first_size));
    auto second = isort(r.rnums<array<int>>(0, 100, 20 - first_size), greater());
    array<int> arr(20);
    for (auto& n : first) arr[i++] = n;
    for (auto& n : second) arr[i++] = n;
    return arr;
}

// Follows a divide and conquer strategy to find the peak
int find_peak(array<int>& arr){
    if (arr.size() == 1)
        return 0;
    size_t start{1}, end{arr.size() - 2}, mid{};
    if (!end)
        return (arr[0] >= arr[1]) ? 0 : 1;
    while (start <= end){
        mid = (start + end) / 2;
        if (arr[mid] < arr[mid + 1])
            start = mid + 1;
        else if (arr[mid] < arr[mid - 1])
            end = mid - 1;
        else
            return mid;
    }
    return -1;
}

int find_peak(array<int>& arr, int left, int right){
    if (left < right){
        int mid{(left + right) / 2};
        // std::cout << left << ' ' << mid << ' ' << right << '\n';
        if (arr[mid] < arr[mid - 1])
            return find_peak(arr, left, mid - 1);
        else if (arr[mid] < arr[mid + 1])
            return find_peak(arr, mid + 1, right);
        else return mid;
    }
    else if (left == right){
        if (!left)
            if (arr[0] >= arr[1]) return 0;
            else return -1;
        else if (right == arr.size() - 1)
            if (arr[right] >= arr[right -1]) return right;
            else return -1;
        else if (arr[left] >= arr[left - 1] && arr[left] >= arr[left + 1])
            return left;
            else return -1;
    }
    else return -1;
}