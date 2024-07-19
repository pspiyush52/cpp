#include <iostream>
#include <algorithm>
#include <vector>
#include "points.h"
#include "stream_insert.h"
#include "lists.h"

template<typename T>
struct less{
	bool operator()(T x, T y){
		return (x < y);
	}
};

template<typename T>
struct identity{
	T& operator()(T& x){
		return x;
	}
	typedef T& (*fun_type)(T&);
	operator fun_type(){
		return invoke;
	}
	private:
		static inline T& invoke(T& x){
			return identity<T>().operator()(x);
		}
};

template<
	typename Collection,
	typename Comparator = less<typename Collection::value_type>,
	typename Projection = identity<typename Collection::value_type>>
	Collection& sort(
		Collection& col,
		Comparator compare = less<typename Collection::value_type>(),
		Projection proj = identity<typename Collection::value_type>())
		{
			long long size{std::end(col) - std::begin(col)}, i{}, j{};
			typename Collection::iterator iter = std::begin(col);
			typename Collection::value_type tmp{};
			
			for (; i < (size - 1); ++i)
				for (j = 1; j < (size - i); ++j){
					if (compare(proj(iter[j]), proj(iter[j - 1]))){
						tmp = iter[j - 1];
						iter[j - 1] = iter[j];
						iter[j] = tmp;
					}
				}
			return col;
		}

int main(void)
{
	std::vector<Point> points{
		{2, 4}, {1, 6}, {3, 9}, {41, 3}, {17, 15}, {12, 5}, {4, -2}, {16, 12}
	};
	namespace ranges = std::ranges;
	/**
	 * The third parameter is the Projection. It specifies the parameter
	 * of comparison between elements in the container.
	 * By passing a lambda which returns the X co-ordinate of the point
	 * we get the collection sorted in order of the value of the X
	 * co-ordinate of every point.
	*/
	ranges::sort(points, std::less<double>(), [](Point& p){
		return p.get_x();
	});
	using namespace __vec__;
	std::cout << points << '\n';

	std::vector<int> nums{3, 4, 5, 1, 3, 9, 45, 21, 6, 18, 94};
	sort(nums);
	std::cout << nums << '\n';

	// Sorting a self defined list
	List<int> list;
	for (int n : nums)
		list.append(n);
	
	sort(list);
	std::cout << "Sorted list : " << list << '\n';

	std::vector<Point> points2{
		{2, 4}, {1, 6}, {3, 9}, {41, 3}, {17, 15}, {12, 5}, {4, -2}, {16, 12}
	};
	std::cout << "\nPoints:\n  " << points2 << '\n';
	sort(points2, less<double>(), [](Point& p){
		return p.get_x();
	});
	std::cout << "Sorting points in the increasing order of X-Coordinates using self defined sort:\n  "
		<< points2 << '\n';

	return 0;
}