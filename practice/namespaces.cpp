#include <iostream>
const double ADJUSTMENT {0.214};

namespace adj{
    double avg(double x, double y){
        return ((x + y - ADJUSTMENT) / 2);
    }
}
namespace no_adj{
    double avg(double x, double y){
        return ((x + y) / 2);
    }
}
/*
    The above two functions have exactly the same signature so defining them
    normally would lead to compiler errors. We use namespaces to resolve such
    conflicts and it allows us to use the two functions using the scope
    resolution operator :: which specifies the namespace to which the function
    belongs.
*/

/*
    The declaration and definition of functions of a namespace can be split
    apart just as in the usual function declaration and definition. We just
    have to enclose the declaration as well as the definition within the same
    namespace.

    Along the same lines splitting the declaration and definition of functions
    of a namespace is allowed accross different files as well. The condition
    being the same that the declarations and definitions must be enclosed
    by the same namespace.
*/

// Declaration
namespace adj{
    double sum(double x, double y);
    double diff(double x, double y);
    double prod(double x, double y);
    double div(double x, double y);
}

namespace no_adj{
    double sum(double x, double y);
    double diff(double x, double y);
    double prod(double x, double y);
    double div(double x, double y);
}

int main(void)
{
    double x{4};
    double y{13};
    double result = adj::avg(4, 13);
    std::cout << "Adjusted average of " << x << " and " << y << " : " << result << '\n';
    result = no_adj::avg(4, 13);
    std::cout << "Non Adjusted average of " << x << " and " << y << " : " << result << '\n';
    std::cout << "Adjusted product of " << x << " and " << y << " : " << adj::prod(x, y) << '\n';
    std::cout << "Non Adjusted product of " << x << " and " << y << " : " << no_adj::prod(x, y) << '\n';
    return 0;
}

// Definition
namespace adj{
    double sum(double x, double y){
        return (x + y - ADJUSTMENT);
    }
    double diff(double x, double y){
        return (x - y - ADJUSTMENT);
    }
    double prod(double x, double y){
        return ((x - ADJUSTMENT) * (y - ADJUSTMENT));
    }
    double div(double x, double y){
        return ((x - ADJUSTMENT) / (y - ADJUSTMENT));
    }
}

namespace no_adj{
    double sum(double x, double y){
        return (x + y);
    }
    double diff(double x, double y){
        return (x - y);
    }
    double prod(double x, double y){
        return (x * y);
    }
    double div(double x, double y){
        return (x / y);
    }
}