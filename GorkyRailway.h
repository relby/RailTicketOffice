#pragma once
#include <stdint.h>
#include <vector>
#include "Trains.h"
#include "Types.h"

class GorkyRailway {
private:
    std::vector<Train*> trains;
public:
    GorkyRailway(uint16_t numberOfLastochka, uint16_t numberOfFirmenniy, uint16_t numberOfSkoriy);
    std::vector<Train*> GetTrainsOfType(TrainType trainType);
    ~GorkyRailway();
};