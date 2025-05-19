#pragma once

#include <memory>
#include <string>

enum class VehicleType
{
    Car,
    Motorcycle,
    Truck,
    Bus
};

struct Vehicle
{
    virtual const std::string& getRegNo() const = 0;
    virtual VehicleType getVehicleType() const = 0;
};

class Car : public Vehicle
{
private:
    std::string regNo_;
    VehicleType type_;
public:
    Car(const std::string& regNo) : regNo_(regNo), type_(VehicleType::Car) {}

    const std::string& getRegNo() const override {
        return regNo_;
    }

    VehicleType getVehicleType() const override {
        return type_;
    }
};

struct VehicleFactory
{
    static std::shared_ptr<Vehicle> createVehicle(VehicleType type, const std::string& regNo)
    {
        switch (type)
        {
        case VehicleType::Car:
            return std::make_shared<Car>(regNo);
            break;
        case VehicleType::Motorcycle:
            break;
        case VehicleType::Bus:
            break;
        case VehicleType::Truck:
            break;
        default:
            return nullptr;
        }

        return nullptr;
    }
};
