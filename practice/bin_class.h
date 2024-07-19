#ifndef __BIN_CLASS_H
#define __BIN_CLASS_H

#include <iostream>

template<typename T>
class bin{
	public:
		bin(T num) : __num(num){}
		bin(T num, T width) : __num(num), __width(width){}
		friend std::ostream& operator<<(std::ostream& output, const bin& b){
			for (T i{b.__width - 1}; i > 0; --i)
				output << (((1LL << i) & b.__num) != 0);
			return output;
		}
	private:
		T __num;
		T __width{8};
};

#endif  // __BIN_CLASS_H