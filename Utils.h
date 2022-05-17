#include <stdint.h>
#include <string>
#include <ctime>
#include <cassert>
#include <iostream>
#include <stdint.h>
#include <utility>
#include <vector>
#include "Types.h"

std::string carTypeToString(CarType type);
std::string seatTypeToString(SeatType type);
std::string trainTypeToString(TrainType type);
std::string ticketTypeToString(TicketType type);

std::tm* parseDate(std::string);
uint16_t chooseOperation();
TrainType chooseTrainType();
CarType chooseCarType(std::vector<CarType> carTypes);
bool checkEqualTM(std::tm, std::tm);

std::string padTo(std::string str, size_t num, char paddingChar);
std::string tmToString(std::tm tm);
std::pair<std::string, std::string> getDateRange();

std::string generateTicketDetails(TrainType trainType, uint16_t traindId, CarType carType, uint16_t carId, uint16_t seatId, SeatType seatType);
uint16_t generatePrice(CarType carType, SeatType seatType);

template <typename T>
T input(std::string message) {
    std::cout << message << '\n';
    T input;
    std::cin >> input;
    return input;
}