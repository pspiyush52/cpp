#include <iostream>

template <typename T, typename... Args>
class crazy : public crazy<Args...>{
    typedef crazy<Args...> Base;
    public:
    	crazy() = default;
        crazy(const T &data, const Args &...args) : m_data{data} {}
        T getData() {
            return this->m_data;
        }
        auto getParentData() {
            return (static_cast<crazy<Args...>*>(this)) -> getData();
        }
        auto getGParentData() {
            return Base::getParentData();
        }

    private:
        T m_data{};
};

template <>
class crazy<int> {
    public:
        crazy() = default;
        crazy(int data) : m_data(data) {}
        int getData() {
            return this->m_data;
        }

    private:
        int m_data{};
};

int main(void)
{
    crazy t(1.2, 'a', 2.5, 1);
    t.getData();
    std::cout << t.getData() << '\n';
    std::cout << t.getParentData() << '\n';
    std::cout << t.getGParentData() << '\n';
    return 0;
}