#include "Car.h"

Car::Car(uint16_t id, CarType type) : id(id), type(type) {
    switch (type) {
    case Sidyachiy:
        seats = std::vector<Seat*>(100);
        for (size_t i = 0; i < seats.size(); i++) {
            seats[i] = new Seat(i + 1, Sidyachiy, None);
        }
        break;
    case Platskart:
        seats = std::vector<Seat*>(54);
        {
            size_t i = 0;
            while (i < seats.size() / 2) {
                seats[i] = new Seat(i + 1, Platskart, Lower);
                i++;
            }
            while (i < seats.size()) {
                seats[i] = new Seat(i + 1, Platskart, Upper);
                i++;
            }
        }
        break;
    case Kupe:
        seats = std::vector<Seat*>(36);
        {
            size_t i = 0;
            while (i < seats.size() / 2) {
                seats[i] = new Seat(i + 1, Kupe, Lower);
                i++;
            }
            while (i < seats.size()) {
                seats[i] = new Seat(i + 1, Kupe, Upper);
                i++;
            }
        }
        break;
    case CB:
        seats = std::vector<Seat*>(18);
        for (size_t i = 0; i < seats.size(); i++) {
            seats[i] = new Seat(i + 1, CB, None);
        }
        break;
    }
}

uint16_t Car::GetId() {
    return id;
}
CarType Car::GetType() {
    return type;
}

std::vector<Seat*> Car::GetSeats() {
    return seats;
}

void Car::Print() {
    std::cout << "Вагон #" << id << ' ' << carTypeToString(type) << '\n';
    for (Seat* seat : seats) {
        seat->Print();
    }
}

Car::~Car() {
    for (Seat* seat : seats) {
        delete seat;
    }
}