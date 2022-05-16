#pragma once
#include <stdint.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Car.h"
#include "Types.h"

class Train {
protected:
    uint16_t id;
    std::vector<Car*> cars;
public:
    Train(uint16_t id);

    void CreateCars(uint16_t sidyachiy, uint16_t platskart, uint16_t kupe, uint16_t cb);
    std::vector<CarType> GetCarsTypes();
    std::vector<Car*> GetCarsOfType(CarType carType);
    virtual TrainType GetType() = 0;
    uint16_t GetId();
    std::vector<Car*> GetCars();
    void Print();
    virtual ~Train();
};

class Lastochka : public Train {
public:
    Lastochka(uint16_t id);
    TrainType GetType() override;
};

class Firmenniy : public Train {
public:
    Firmenniy(uint16_t id);
    TrainType GetType() override;
};

class Skoriy : public Train {
public:
    Skoriy(uint16_t id);
    TrainType GetType() override;
};