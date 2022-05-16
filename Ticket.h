#pragma once
#include <stdint.h>
#include <string>
#include <ctime>
#include <stdio.h>
#include "Trains.h"

class Ticket {
private:
    TicketType type;
    std::tm date;
    std::string owner;
    Train* train;
    Car* car;
    Seat* seat;
    uint16_t price;
public:
    Ticket();
    Ticket(TicketType type, std::tm date, std::string buyer, Train* train, Car* car, Seat* seat);
    TicketType GetType();
    std::string GetOwner();
    std::tm GetDate();
    std::string GetDetails();
    Train* GetTrain();
    Car* GetCar();
    Seat* GetSeat();
    uint16_t GetPrice();
};