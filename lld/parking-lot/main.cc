#include <cstddef>
#include <iostream>
#include <vector>
#include <memory>

#include "vehicle.hpp"
#include "parking_slot.hpp"

static const size_t PARKING_LOT_SIZE = 1000;


size_t ParkingSlot::counter_{0};


// Parking Lot Class
class SingletonParkingLot
{
private:
    SingletonParkingLot()
    {
        parking_lot_.resize(PARKING_LOT_SIZE);
    }

    size_t idx = 0;
    std::vector<ParkingSlot> parking_lot_;

public:
    static SingletonParkingLot& getInstance()
    {
        // Thread safe Meyer's singleton
        static SingletonParkingLot instance;
        return instance;
    }

    void ParkVehcile(std::shared_ptr<Vehicle> vehicle)
    {

    }

    SingletonParkingLot(SingletonParkingLot const&) = delete;
    SingletonParkingLot& operator=(SingletonParkingLot const&) = delete;
};


int main()
{
    auto car = VehicleFactory::createVehicle(VehicleType::Car, "UP12376");
    std::cout << "Vehicle of type car has reg No: "  << car->getRegNo() << std::endl;

    SingletonParkingLot::getInstance().ParkVehcile(car);
}
