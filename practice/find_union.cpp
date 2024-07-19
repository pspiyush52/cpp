#include "stream_insert.h"

template <typename T>
std::list<T> union_func(const std::list<T>& l1, const std::list<T>& l2){

    std::list<T> result;
    auto itl1 = l1.begin();
    auto itl2 = l2.begin();
    
    //YOUR CODE WILL GO BELOW THIS LINE 
    //DON'T MODIFY ANYTHING ABOVE THIS LINE
    while((itl1 != l1.end()) && (itl2 != l2.end())){
		if (*itl1 == *itl2)
		{
			result.push_back(*itl1);
			++itl1;
			++itl2;
		}
        else if (*itl1 < *itl2){
			result.push_back(*itl1);
			++itl1;
		}
        else{
			result.push_back(*itl2);
			++itl2;
		}
    }
    if (itl1 != l1.end())
        for (; itl1 != l1.end(); ++itl1)
            result.push_back(*itl1);
    else if (itl2 != l2.end())
        for (; itl2 != l2.end(); ++itl2)
            result.push_back(*itl2);
    //YOUR CODE WILL GO ABOVE THIS LINE 
    //DON'T MODIFY ANYTHING BELOW THIS LINE
    return result;

}

int main(void)
{
	std::list<int> l1{3, 4, 5, 7, 11, 17, 24, 25, 29, 33};
	std::list<int> l2{1, 4, 6, 7, 9};
	std::list<int> result = union_func(l1, l2);
	using namespace __list__;
	std::cout << result << '\n';
	return 0;
}