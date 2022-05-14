#pragma once
#include <cstddef>
#include <iostream>
#include <string>
#include "Types.h"
#include "Utils.h"
#include "Ticket.h"

class Seat {
private:
    uint16_t id;
    CarType carType;
    SeatType type;
    bool isReserved;
    bool isBought;
    std::string owner;
public:
    Seat();
    Seat(uint16_t id, CarType carType, SeatType type);
    uint16_t GetId();
    SeatType GetType();
    bool IsBought();
    bool IsReserved();
    //void Reserve(std::string buyer);
    Ticket BuyTicket(std::tm date, std::string buyer);
    void Print();
};