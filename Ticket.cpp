#include "Ticket.h"

Ticket::Ticket() {}
Ticket::Ticket(std::tm date, std::string buyer, Train* train, Car* car, Seat* seat) : date(date), owner(buyer), train(train), car(car), seat(seat) {}

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