#include <iostream>
#include <string>
#include <type_traits>
#include <typeinfo>
/*
 * We can enforce conditions on class templates by using static asserts
 * and type traits using the syntax below.
 */
template <typename T, typename P>
struct Map
{
	static_assert(std::is_integral_v<T>, "Keys should be of integral types.");
	static_assert(std::is_same_v<P, std::string>, "Values can only be std::strings.");

	public:
		Map(T key, P value) : m_key(key), m_value(value){}
	
	private:
		T m_key;
		P m_value;
};

int main(void)
{
	Map<unsigned int, std::string> m3(22.1, "This");
	// Map m3(22, "This");  // error
	return 0;
}