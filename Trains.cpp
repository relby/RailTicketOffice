#include "Trains.h"
#include "Types.h"
#include <iostream>

Train::Train(uint16_t id) : id(id) {}

void Train::CreateCars(uint16_t sidyachiy, uint16_t platskart, uint16_t kupe, uint16_t cb) {
    cars = std::vector<Car*>();
    size_t idOfCar = 1;
    for (int i = 0; i < sidyachiy; i++) {
        cars.push_back(new Car(idOfCar++, Sidyachiy));
    }
    for (int i = 0; i < platskart; i++) {
        cars.push_back(new Car(idOfCar++, Platskart));
    }
    for (int i = 0; i < kupe; i++) {
        cars.push_back(new Car(idOfCar++, Kupe));
    }
    for (int i = 0; i < cb; i++) {
        cars.push_back(new Car(idOfCar++, CB));
    }
}

Car* Train::GetCar(uint16_t idOfCar) {
    if (idOfCar > cars.size() || idOfCar == 0) {
        return nullptr;
    }
    return cars[idOfCar - 1];
};

void Train::Print() {
    std::cout << id << '\n';
    for (Car* car : cars) {
        car->Print();
    }
}

Train::~Train() {
    for (Car* car : cars) {
        delete car;
    }
}

Lastochka::Lastochka(uint16_t id) : Train(id) {
    CreateCars(8, 0, 0, 0);
}

TrainType Lastochka::GetType() {
    return LastochkaType;
}

Firmenniy::Firmenniy(uint16_t id) : Train(id) {
    CreateCars(0, 4, 6, 2);
}

TrainType Firmenniy::GetType() {
    return FirmenniyType;
}

Skoriy::Skoriy(uint16_t id) : Train(id) {
    CreateCars(0, 8, 4, 0);
}

TrainType Skoriy::GetType() {
    return SkoriyType;
}