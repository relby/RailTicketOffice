#include "Seat.h"

Seat::Seat() {}
Seat::Seat(uint16_t id, CarType carType, SeatType type) : id(id), carType(carType), type(type), isReserved(false), isBought(false), owner("") {}
uint16_t Seat::GetId() {
    return id;
}

SeatType Seat::GetType() {
    return type;
}

bool Seat::IsBought() {
    return isBought;
}

bool Seat::IsReserved() {
    return isReserved;
}

// void Seat::Reserve(std::string buyer) {
//     isReserved = true;
// }

Ticket Seat::BuyTicket(std::tm date, std::string buyer) {
    Ticket t = Ticket(buyer, date, "123123");
    owner = buyer;
    isBought = true;
    return t;
}

void Seat::Print() {
    std::cout << "Место #" << id << ' ' << seatTypeToString(type) << '\n';
}