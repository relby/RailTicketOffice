#pragma once
#include "Trains.h"
#include "Types.h"

class GorkyRailway {
private:
    std::vector<Train*> trains;
public:
    GorkyRailway(uint16_t numberOfLastochka, uint16_t numberOfFirmenniy, uint16_t numberOfSkoriy);
    Train* GetTrain(TrainType trainType);
    ~GorkyRailway();
};