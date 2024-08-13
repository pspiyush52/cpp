#ifndef __TUPLES_H
#define __TUPLES_H

template<typename first_tp, typename second_tp>
class Pair {
    public:
        Pair() = default;
        Pair(const first_tp& first, const second_tp& second):
            m_first{first}, m_second{second} {}
        Pair(first_tp&& first, second_tp&& second):
            m_first{first}, m_second{second} {}
        
        const first_tp& getFirst() const {
            return this->m_first;
        }
        const second_tp& getSecond() const {
            return this->m_second;
        }
        void setFirst(const first_tp& value) {
            this->m_first = value;
        }
        void setSecond(const second_tp& value) {
            this->m_second = value;
        }

    private:
        first_tp m_first{};
        second_tp m_second{};
};

template<typename first_tp, typename second_tp, typename third_tp>
class Triple : public Pair<first_tp, second_tp> {
    public:
        Triple(const first_tp& first, const second_tp& second, const third_tp& third):
            Pair<first_tp, second_tp>(first, second), m_third{third} {}
        Triple(first_tp&& first, second_tp&& second, third_tp&& third):
            Pair<first_tp, second_tp>(first, second), m_third{third} {}
        
        const third_tp& getThird() const {
            return this->m_third;
        }
        third_tp& getThird() {
            return this->m_third;
        }
        void setThird(const third_tp& value) {
            this->m_third = value;
        }
    
    private:
        third_tp m_third;
};

#endif  // __TUPLES_H