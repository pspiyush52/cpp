#include <iostream>

template<typename ret_tp, typename T, typename ...Args>
ret_tp sum(const T& cur, const Args& ...rest);

int main(void)
{
    std::cout << sum<double>(1, 3.256, 12, 'A', 0.178);
    return 0;
}

template<typename ret_tp>
ret_tp sum() { return {}; }

template<typename ret_tp, typename T, typename ...Args>
ret_tp sum(const T& cur, const Args& ...rest) {
    ret_tp s = {};
    s = cur + sum<ret_tp>(rest...);
    return s;
}
