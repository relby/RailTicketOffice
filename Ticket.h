#pragma once
#include <stdint.h>
#include <string>
#include <ctime>
#include <stdio.h>
#include "Trains.h"

class Ticket {
private:
    std::string owner;
    std::tm date;
    Train* train;
    Car* car;
    Seat* seat;
    uint16_t price;
public:
    Ticket();
    Ticket(std::tm date, std::string buyer, Train* train, Car* car, Seat* seat);
    std::string GetOwner();
    std::tm GetDate();
    std::string GetDetails();
    Train* GetTrain();
    Car* GetCar();
    Seat* GetSeat();
};