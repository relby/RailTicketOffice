#include "Trains.h"
#include "Types.h"

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

std::vector<CarType> Train::GetCarsTypes() {
    std::vector<CarType> out;
    for (Car* car : cars) {
        if (std::find(out.begin(), out.end(), car->GetType()) == out.end()) {
            out.push_back(car->GetType());
        }
    }
    return out;
}

std::vector<Car*> Train::GetCarsOfType(CarType carType) {
    std::vector<Car*> out;
    for (Car* car : cars) {
        if (car->GetType() == carType) {
            out.push_back(car);
        }
    }
    return out;
}

uint16_t Train::GetId() {
    return id;
}

std::vector<Car*> Train::GetCars() {
    return cars;
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