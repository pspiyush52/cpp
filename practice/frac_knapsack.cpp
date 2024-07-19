#include "frac_knapsack.h"
#include "defs.h"

void frac_knapsack(Objects& obj, const int CAPACITY){
    int knapsack_weight{}, current_weight{}, weight_to_be_included{};
    double total_profit{};
    repeats(obj.size()){
        current_weight = obj[i].weight();        
        if (knapsack_weight + current_weight > CAPACITY)
        {
            weight_to_be_included = CAPACITY - knapsack_weight;
            knapsack_weight += weight_to_be_included;
            total_profit += weight_to_be_included * obj[i].profit_per_unit_weight();
            break;
        }
        else
        {
            knapsack_weight += current_weight;
            total_profit += obj[i].profit();
        }
    }
    std::cout << "Total weight: " << knapsack_weight << '\n';
    std::cout << "Total profit: " << total_profit << '\n';
}

int main(void)
{
    // Objects O{{18, 25}, {15, 24}, {10, 15}};
    Objects O{{2, 10}, {3, 5}, {5, 15}, {7, 7}, {1, 6}, {4, 18}, {1, 3}};
    std::cout << "The objects in decreasing order of profit per unit weight:\n";
    std::cout << '\t' << O << "\n\n";
    frac_knapsack(O, 5);
    return 0;
}