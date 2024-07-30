#ifndef __STOCKS_H
#define __STOCKS_H

#include "carr.h"
#include <iomanip>

class Price {
    public:
        Price() = default;
        Price(double p): price(p) {}
        operator double() const;
        friend std::ostream& operator<<(std::ostream& out, const Price& p);
    private:
        double price{};
};
class StockDetails {
    public:
        StockDetails(const array<Price>& Prices);
        Price getMinPrice() const;
        int getMinPriceDay() const;
        Price getMaxPrice() const;
        int getMaxPriceDay() const;
        Price getMaxProfit() const;
        int getBuyingDay() const;
        int getSellingDay() const;

    private:
        Price max_profit;
        int start_index;
        int end_index;
        Price min_price;
        int min_day;
        Price max_price;
        int max_day;
};

// Constructor that takes the list of prices and calculates the days of
// purchase and selling a stock for maximum profit.
StockDetails::StockDetails(const array<Price>& Prices) {
    int possible_start{}, start{}, end{};
    double cur_max{__DBL_MIN__}, max_ends_here{}, priceDifference{};
    this->min_price = Prices[0];
    this->max_price = Prices[0];
    for (size_t i{1}; i < Prices.size(); ++i) {
        if (Prices[i] < this->min_price) {
            this->min_price = Prices[i];
            this->min_day = i;
        }
        if (Prices[i] > this->max_price) {
            this->max_price = Prices[i];
            this->max_day = i;
        }
        priceDifference = Prices[i] - Prices[i - 1];
        max_ends_here += priceDifference;
        if (cur_max < max_ends_here) {
            cur_max = max_ends_here;
            start = possible_start;
            end = i;
        }
        if (max_ends_here < 0) {
            max_ends_here = {};
            possible_start = i;
        }
    }
    // Upon termination of the above for loop:
    // cur_max holds the maximum profit,
    // start holds the day on which the stock must be purchased
    // end holds the day on which it must be sold
    // We can encapsulate all this data in one object and return
    // it to the calling function.
    this->max_profit = cur_max;
    this->start_index = start;
    this->end_index = end;
}

Price StockDetails::getMinPrice() const {
    return this->min_price;
}
int StockDetails::getMinPriceDay() const {
    return this->min_day;
}
Price StockDetails::getMaxPrice() const {
    return this->max_price;
}
int StockDetails::getMaxPriceDay() const {
    return this->max_day;
}
Price StockDetails::getMaxProfit() const {
    return this->max_profit;
}
int StockDetails::getBuyingDay() const {
    return this->start_index;
}
int StockDetails::getSellingDay() const {
    return this->end_index;
}
Price::operator double() const {
    return this->price;
}
std::ostream& operator<<(std::ostream& out, const Price& p) {
    out << '$' << std::setprecision(4) << p.price;
    return out;
}

#endif  // __STOCKS_H