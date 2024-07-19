#include <iostream>
#include <cstring>
#include <memory>

class Vehicle {
    public:
        virtual void start() = 0;
        virtual ~Vehicle(){}
};

class Car : public Vehicle {
    public:
        virtual void start() {
            std::cout << "The car has started\n";
        }
};

class Bike : public Vehicle {
    public:
        virtual void start() {
            std::cout << "The bike has started\n";
        }
};

class VehicleFactory {
    public:
        std::unique_ptr<Vehicle> makeVehicle(const char* str) {
            if (std::strcmp(str, "Car") == 0)
                return std::make_unique<Car>();
            else if (std::strcmp(str, "Bike") == 0)
                return std::make_unique<Bike>();
            else
                return {};
        }
};

int main(void)
{
    VehicleFactory vf{};
    auto v = vf.makeVehicle("Car");
    v->start();
    return 0;
}
