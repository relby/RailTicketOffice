#pragma once
#include <cstddef>
#include <stdint.h>
#include <vector>
#include "Types.h"
#include "Seat.h"

class Car {
private:
    uint16_t id;
    CarType type;
    std::vector<Seat*> seats;
public:
    Car(uint16_t id, CarType type);

    uint16_t GetId();
    CarType GetType();
    std::vector<Seat*> GetSeats();
    void Print();
    ~Car();
};