#include "print.h"
#include "stocks.h"
#include "frand.h"
#include "deque.h"

void printDailyPrices(const array<Price>& Prices);

int main(void)
{
    array<Price> Prices(11);
    printer(rng().randoms<deque<double>, double>(10, 100, Prices.size())) >> Prices;
    print("Initial stock price:", Prices[0]);
    std::cout << "\nDaily stock prices:\n  ";
    printDailyPrices(Prices);

    StockDetails mp{Prices};
    print("\n\nThe maximum possible profit is", mp.getMaxProfit());
    print(
        "If bought on day", mp.getBuyingDay(),
        "at", Prices[mp.getBuyingDay()],
        "and sold on day", mp.getSellingDay(),
        "at", Prices[mp.getSellingDay()]
    );
    print("\nMinimum price:", mp.getMinPrice());
    print("Maximum price:", mp.getMaxPrice());
    return 0;
}

void printDailyPrices(const array<Price>& Prices) {
    size_t i{1};
    for (; i < Prices.size() - 1; ++i)
        std::cout << Prices[i] << "  ->  ";
    std::cout << Prices[i];
}
