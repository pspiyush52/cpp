#include <iostream>
#include <queue>
#include <functional>
#include <cstring>

template<typename T, typename Sequence, typename Compare>
void print(const char* name, std::priority_queue<T, Sequence, Compare>& q){
	std::cout << name << '\t';
	for (; !q.empty(); q.pop())
		std::cout << q.top() << ' ';
	std::cout << '\n';
}

int main(void)
{
	const int nums[] = {6, 4, 8, 1, 3, 5, 7, 0, 9};
	size_t size = std::size(nums);
	std::priority_queue<int> q1;
	for (int n : nums)
		q1.push(n);	
	print("q1", q1);

	std::priority_queue<int, std::vector<int>, std::greater<int>> q2(nums, nums + size);
	print("q2", q2);

	std::priority_queue q3(nums, nums + size, std::greater<int>());
	print("q3", q3);

	const auto names = {"Niharika", "Piyush", "Sam", "Sarah", "Roger"};

	// Using a lambda as a comparison function object
	std::priority_queue q4(names.begin(), names.end(), [](const char* lhs, const char* rhs){
		return (std::strcmp(lhs, rhs) > 0);
	});
	print("q4", q4);

	struct strcomp{
		bool operator()(const char* lhs, const char* rhs){
			return (std::strcmp(lhs, rhs) > 0);
		}
	};
	// Providing a custom comparison function object type
	std::priority_queue<const char*, std::vector<const char*>, strcomp> q5(names.begin(), names.end());
	print("q5", q5);

	// Providing a custom comparison function object
	std::priority_queue q6(names.begin(), names.end(), strcomp());
	print("q6", q6);

    auto cmp = [](const char* lhs, const char* rhs){
		return (std::strcmp(lhs, rhs) > 0);
	};

    std::priority_queue q7(names.begin(), names.end(), cmp);
    print("q7", q7);

    // If we want to use a different container we will have to use the
    // complete syntax while declaring the priority queue.
    std::priority_queue<
        const char*,
        std::vector<const char*>,
        decltype(cmp)
    > q8(names.begin(), names.end(), cmp);
    print("q8", q8);
	
	return 0;
}