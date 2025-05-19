#pragma once
#include <cstddef>
#include "vehicle.hpp"

// Parking Slot
struct ParkingSlot
{
private:
    size_t slotID_;
    std::shared_ptr<Vehicle> vehicle_;
    static size_t counter_;

public:
    ParkingSlot() : slotID_(++counter_), vehicle_(nullptr) {}

    size_t getSlotID() const
    {
        return slotID_;
    }

    bool isOccupied() const
    {
        return (vehicle_ != nullptr);
    }

    void OccupySlot(std::shared_ptr<Vehicle> vehicle)
    {
        if(vehicle == nullptr)
            return;
        vehicle_ = vehicle;
    }
};
