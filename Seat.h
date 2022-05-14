#pragma once
#include <cstddef>
#include <iostream>
#include <string>
#include "Types.h"
#include "Utils.h"

class Seat {
private:
    uint16_t id;
    CarType carType;
    SeatType type;
public:
    Seat();
    Seat(uint16_t id, CarType carType, SeatType type);
    uint16_t GetId();
    SeatType GetType();
    void Print();
};