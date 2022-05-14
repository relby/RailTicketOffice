#pragma once
#include <stdint.h>
#include <vector>
#include "Car.h"
#include "Types.h"

class Train {
protected:
    uint16_t id;
    std::vector<Car*> cars;
public:
    Train(uint16_t id);

    void CreateCars(uint16_t sidyachiy, uint16_t platskart, uint16_t kupe, uint16_t cb);
    virtual TrainType GetType() = 0;
    uint16_t GetId();
    Car* GetCar(uint16_t idOfCar);
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