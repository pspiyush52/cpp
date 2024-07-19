#ifndef __FRAC_KNAPSACK_H
#define __FRAC_KNAPSACK_H

#include <iostream>
#include <initializer_list>
#include "isort.h"
#include "exceptions.h"

class Objects;
class Object{
    friend class Objects;
    public:
        int weight(){ return this->__weight; }
        int profit(){ return this->__profit; }
        double profit_per_unit_weight(){ return this->__ppu; }
        Object& set(int weight, int profit){
            this->__weight = weight;
            this->__profit = profit;
            this->__ppu = 1.0 * profit / weight;
            return *this;
        }
        friend std::ostream& operator<<(std::ostream& output, Object& obj){
            output << "(Weight: " << obj.__weight << ", Profit: " << obj.__profit << ')';
            return output;
        }
    private:
        Object() = default;
        int __weight{};
        int __profit{};
        double __ppu{};
};

class Objects{
    public:
        Objects(size_t size){
            this->__arr = new Object[size];
            this->__size = size;
        }
        Objects(std::initializer_list<std::initializer_list<int>> args){
            this->__arr = new Object[args.size()];
            this->__size = args.size();
            auto iter = args.begin();
            auto end = args.end();
            for (int i{}; iter != end; ++iter, ++i){
                if (iter->size() != 2)
                    throw ArgError("Invalid number of arguments for object");
                this->__arr[i].set(*(iter->begin()), *(iter->begin() + 1));
            }
            isort<Objects, greater, ppu>(*this);
        }
        Object& operator[](size_t i){ return (*(this->__arr + i)); }
        size_t size(){ return this->__size; }
        ~Objects(){
            delete[] this->__arr;
            this->__arr = nullptr;
            this->__size = 0;
        }
        friend std::ostream& operator<<(std::ostream& output, Objects& objs){
            output.put('{');
            size_t i{}, upto{objs.size() - 1};
            for (; i < upto; ++i)
                output << objs[i] << ", ";
            output << objs[i];
            output.put('}');
            return output;
        }
    private:
        Object* __arr{};
        size_t __size{};
        struct ppu{
            double operator()(Object& obj){
                return obj.profit_per_unit_weight();
            }
        };
};

#endif  // __FRAC_KNAPSACK_H