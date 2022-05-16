#include "Ticket.h"
#include <stdint.h>

Ticket::Ticket() {}
Ticket::Ticket(TicketType type, std::tm date, std::string buyer, Train* train, Car* car, Seat* seat) : type(type), date(date), owner(buyer), train(train), car(car), seat(seat) {
    price = generatePrice(car->GetType(), seat->GetType());
}

TicketType Ticket::GetType() {
    return type;
}

std::string Ticket::GetOwner() {
    return owner;
}
std::tm Ticket::GetDate() {
    return date;
}
std::string Ticket::GetDetails() {
    return generateTicketDetails(train->GetType(), train->GetId(), car->GetType(), car->GetId(), seat->GetId());
}
Train* Ticket::GetTrain() {
    return train;
}
Car* Ticket::GetCar() {
    return car;
}
Seat* Ticket::GetSeat() {
    return seat;
}

uint16_t Ticket::GetPrice() {
    return price;
}