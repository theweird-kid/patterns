/*
Requirements

### Functional Requirements
- **Vehicle entry/exit:**
  ● Allow vehicles (cars, bikes, trucks, etc.) to enter and exit the parking lot.
  ● Provide a ticket with an entry time for every vehicle.

- **Parking allocation:**
  ● Identify and assign an appropriate parking slot based on vehicle type and size restrictions.
  ● Track available vs. occupied slots in real-time.

- **Payment handling:**
  ● Process payments upon exit, calculating fees based on parked duration, vehicle type, or other parameters.
  ● Support different payment modes (cash, card, mobile).

- **Reservation/Pre-booking (optional):**
  ● Allow a user to pre-book a parking spot.

- **Monitoring and Alerts:**
  ● Send alerts when the parking lot is full or near capacity.
  ● Provide real-time reports on occupancy.

### Non-Functional Requirements
- **Scalability:**
  ● The system should handle adding multiple floors or lots seamlessly.

- **Concurrency:**
  ● Concurrency must be handled for vehicle entries/exits to avoid race conditions when allocating or deallocating a slot.

- **Maintainability/Extensibility:**
  ● The architecture should allow changes such as different payment strategies or additional vehicle types.

- **Reliability:**
  ● Ensure that the system gracefully handles errors (e.g., ticket not found at exit).

---

## Design Patterns Used

- **Singleton Pattern:**
  ● To ensure that the `ParkingLot` instance is globally accessible and only instantiated once.

- **Factory Pattern:**
  ● To create different types of vehicles (such as `Car`, `Truck`, `Motorcycle`) without exposing the instantiation logic to the client and to support added vehicle types in the future.

- **Strategy Pattern:**
  ● For calculating parking fees. Different strategies can be implemented based on vehicle type, duration, time of day, etc., and instantiated at runtime, enabling easy fee calculation modifications.

- **Observer Pattern (optional):**
  ● To notify external systems or components (e.g., mobile app, display board) when the parking occupancy changes or when near capacity.

- **Composite Pattern (optional):**
  ● If the parking lot consists of multiple levels and sectors, the composite pattern can organize these hierarchically, treating a floor or a zone uniformly.

---

## Class Design

Below is a non-exhaustive list of classes and a brief description of their responsibilities:

- **ParkingLot**
  ● **Responsibility:**
  Manages the overall parking lot, including a collection of parking floors. Provides entry and exit APIs.
  ● **Key Methods:**
  `allocateSlot(Vehicle vehicle)`, `freeSlot(Ticket ticket)`, `getAvailableSlots()`

- **ParkingFloor**
  ● **Responsibility:**
  Represents a single floor in the parking lot. Manages a collection of `ParkingSlot` instances.
  ● **Key Methods:**
  `getAvailableSlot(Vehicle vehicle)`

- **ParkingSlot**
  ● **Responsibility:**
  Represents an individual parking space with attributes like slot number, size, and occupancy status.
  ● **Key Attributes:**
  `slotId`, `slotType` (for motorbike, compact, large, etc.), `isOccupied`

- **Vehicle (Abstract Class)**
  ● **Responsibility:**
  Base class for different types of vehicles. Contains common attributes such as registration number and model.
  ● **Derived Classes:**
  `Car`, `Motorcycle`, `Truck`

- **Ticket**
  ● **Responsibility:**
  Represents the parking ticket issued to a vehicle at entry. Contains information such as entry time, allocated slot, and vehicle details.
  ● **Key Attributes:**
  `ticketId`, `entryTime`, `exitTime`, `parkingSlot`

- **Payment**
  ● **Responsibility:**
  Handles payment processes upon exit; potentially implemented using the Strategy pattern to allow different fee calculations or payment gateways.
  ● **Key Methods:**
  `processPayment(Ticket ticket)`, `calculateFee(Ticket ticket)`

- **FeeCalculator (Strategy Pattern Interface)**
  ● **Responsibility:**
  Provides a contract for fee calculation methods.
  ● **Implementations:**
  `FixedRateFeeCalculator`, `TimeBasedFeeCalculator`

- **VehicleFactory (Factory Pattern)**
  ● **Responsibility:**
  Provides a method to create vehicles of various types based on input parameters.
  ● **Key Method:**
  `createVehicle(type: string, registrationNo: string, ...)`

---

## Example Usage Scenario

1. **Vehicle Entry:**
   ● A vehicle arrives and the system uses `VehicleFactory` to create the appropriate vehicle instance.
   ● `ParkingLot.allocateSlot(Vehicle)` is called. This method delegates to the corresponding `ParkingFloor` to find an available slot that matches the vehicle's requirements.
   ● A `Ticket` is generated reflecting the allocated slot and entry time.

2. **Vehicle Exit:**
   ● The vehicle presents the ticket at exit.
   ● The system uses the associated `Ticket` to calculate the parking fee via the `Payment` module (which uses a `FeeCalculator` strategy).
   ● Payment processing is done and then `ParkingLot.freeSlot(Ticket)` is called so that the slot is marked available.

3. **Real-time Monitoring:**
   ● If implemented, an Observer might listen to changes in the parking lot occupancy (e.g., when a slot is allocated or freed), and update a display board or send notifications regarding full capacity.

*/
