#include "Seat.h"

Seat::Seat() {}
Seat::Seat(uint16_t id, CarType carType, SeatType type) : id(id), carType(carType), type(type), isReserved(false), isBought(false), owner("") {}
uint16_t Seat::GetId() {
    return id;
}

SeatType Seat::GetType() {
    return type;
}

// void Seat::Reserve(std::string buyer) {
//     isReserved = true;
// }

void Seat::Print() {
    std::cout << "Место #" << id << ' ' << seatTypeToString(type) << '\n';
}