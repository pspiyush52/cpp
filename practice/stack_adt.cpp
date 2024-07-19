#include <iostream>
#include "stack_adt.h"
#include "defs.h"

template<typename T>
class Stack : public StackBase<T>{
	public:
		Stack(size_t size) : __arr(new T[size]), __cur(0), __size(size){}
		bool is_empty(){ return (this->__cur == 0); }
		bool is_full(){ return (this->__cur == this->__size); }
		StackBase<T>& push(const T& item){
			if (!this->is_full())
				this->__arr[this->__cur++] = item;
			return *this;
		}
		StackBase<T>& push(T&& item){
			if (!this->is_full())
				this->__arr[this->__cur++] = item;
			return *this;
		}
		StackBase<T>& pop(){
			if (!this->is_empty())
				--this->__cur;
			return *this;
		}
		const T& top(){ return (this->__arr[this->__cur - 1]); }
		~Stack(){
			delete[] this->__arr;
			this->__cur = this->__size = 0;
		}
		
	private:
		T* __arr{};
		size_t __cur{};
		size_t __size{};

		void stream_insert(std::ostream& output){
			output << "[(";
			if (!is_empty()){
				T* iter = __arr;
				T* before_end = __arr + __cur - 1;
				for (; iter != before_end; ++iter)
					output << *iter << ", ";
				output << *iter;
			}
			output << ") <Stack object at " << this << ">]";
		}
};

int main(void)
{
	Stack<int> s(10);
    std::cout << "Empty stack:\n\t" << s << '\n';
    int arr[] = {4, 2, 5, 1, 65, 12, 9, 45, 18, 97, 64, 8, 17, 102, 37, 84, 99, 62, 33, 74};
	for (int num : arr)
        s.push(num);
	std::cout << "\nStack after pushing elements into it:\n\t" << s << "\n\n";
    repeat(7)
        std::cout << '\t' << s.pop() << '\n';
	std::cout << "\nStack after popping 7 elements followed by a single push operation:\n\t" << s.push(8) << '\n';
	return 0;
}