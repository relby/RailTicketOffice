#include <string>
#include <ctime>
#include <iostream>
#include "Types.h"

std::string carTypeToString(CarType type);
std::string seatTypeToString(SeatType type);
std::tm* parseDate(std::string);