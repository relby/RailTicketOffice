#include "GorkyRailway.h"
#include <stdint.h>
#include <vector>

GorkyRailway::GorkyRailway(uint16_t numberOfLastochka, uint16_t numberOfFirmenniy, uint16_t numberOfSkoriy) : trains(std::vector<Train*>()) {
    for (uint16_t i = 0; i < numberOfLastochka; i++) {
        trains.push_back(new Lastochka(i + 1));
    }
    for (uint16_t i = 0; i < numberOfFirmenniy; i++) {
        trains.push_back(new Firmenniy(i + 1));
    }
    for (uint16_t i = 0; i < numberOfSkoriy; i++) {
        trains.push_back(new Skoriy(i + 1));
    }
}

Train* GorkyRailway::GetTrain(TrainType trainType) {
    for (Train* train : trains) {
        if (train->GetType() == trainType) {
            return train;
        }
    }
    return nullptr;
}

GorkyRailway::~GorkyRailway() {
    for (Train* train : trains) {
        delete train;
    }
}