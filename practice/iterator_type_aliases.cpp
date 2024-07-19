#include <iterator>

template<typename T>
class __sample_iterator{
    public:
        // Type Aliases:
        using iterator_category =   std::input_iterator_tag;
        using difference_type =     std::ptrdiff_t;
        using value_type =          T;
        using pointer =             value_type*;
        using reference =           value_type&;
};

template<typename T>
class __sample_iterable{
    public:
        using iterator = __sample_iterator<T>;
};