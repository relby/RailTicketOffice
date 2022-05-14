#include "Utils.h"
#include <string>


std::string carTypeToString(CarType type) {
    switch (type) {
    case Sidyachiy:
        return "Сидячий";
    case Platskart:
        return "Плацкарт";
    case Kupe:
        return "Купе";
    case CB:
        return "СВ";
    }
    return "unreachable";
}

std::string seatTypeToString(SeatType type) {
    switch (type) {
    case Upper:
        return "Верхний";
    case Lower:
        return "Нижний";
    case None:
        return "";
    }
    return "unreachable";
}

std::string trainTypeToString(TrainType type) {
    switch (type) {
    case LastochkaType:
        return "Ласточка";
    case FirmenniyType:
        return "Фирменный";
    case SkoriyType:
        return "Скорый";
    }
    return "unreachable";
}

std::tm* parseDate(std::string date_str) {
    int pos = date_str.find('/');
    if (pos != 2 || date_str.size() != 5) return nullptr;

    int day = atoi(date_str.substr(pos - 2, 2).c_str());
    int month = atoi(date_str.substr(pos + 1, 2).c_str());

    if (day <= 0 || day > 31) return nullptr;
    if (month <= 0 || month > 12) return nullptr;

    std::time_t t = std::time(0);
    for (int i = 0; i < 31 ; i++) {
        std::tm date = *std::localtime(&t);
        if (day == date.tm_mday && month == (date.tm_mon + 1)) {
            return std::localtime(&t);
        }
        t += 60 * 60 * 24; // adding one day to the current time
    }
    return nullptr;
}


uint16_t chooseOperation() {
    uint16_t input = -1;
    std::cout << "What do you want to do?\n";
    std::cout << "[0]: Buy Tickets\n";
    std::cout << "[1]: Check Seat\n";
    std::cout << "[2]: Get Tickets by name\n";
    std::cout << "[3]: Quit\n";
    while (!(input >= 0 && input <= 3)) {
        std::cin >> input;
    }
    return input;
}
TrainType chooseTrain() {
    uint16_t input = -1;
    std::cout << "Choose train Type\n";
    std::cout << "[" << LastochkaType << "]" << ": Lastochka\n";
    std::cout << "[" << FirmenniyType << "]" << ": Firmenniy\n";
    std::cout << "[" << SkoriyType << "]" << ": Skoriy\n";
    while (!(input >= 0 && input <= 2)) {
        std::cin >> input;
    }
    return (TrainType)input;
}

bool checkEqualTM(std::tm tm1, std::tm tm2) {
    return tm1.tm_mday == tm2.tm_mday && tm1.tm_mon == tm2.tm_mon;
}

std::string padTo(std::string str, size_t num, char paddingChar) {
    if(num > str.size())
        str.insert(0, num - str.size(), paddingChar);
    return str;
}

std::string tmToString(std::tm tm) {
    return padTo(std::to_string(tm.tm_mday), 2, '0') + "/" +
                         padTo(std::to_string(tm.tm_mon + 1), 2, '0');
}

std::pair<std::string, std::string> getDateRange() {
    std::time_t t = std::time(0);
    std::tm now = *std::localtime(&t);
    t += 60 * 60 * 24 * 30; // Adding 1 month to the time counter
    std::tm in1Month = *std::localtime(&t);
    std::string nowStr = tmToString(now);
    std::string in1MonthStr = tmToString(in1Month);
    return std::pair<std::string, std::string>(nowStr, in1MonthStr);

}


std::string generateTicketDetails(TrainType trainType, uint16_t trainId, CarType carType, uint16_t carId, uint16_t seatId /*SeatType seatType*/ ) {
    // TODO: add SeatType
    std::string trainTypeStr = trainTypeToString(trainType);
    std::string carTypeStr = carTypeToString(carType);
    std::string trainIdStr = std::to_string(trainId);
    std::string carIdStr = std::to_string(carId);
    std::string seatIdStr = std::to_string(seatId);
    return trainTypeStr + " #" + trainIdStr + " " + carTypeStr + " Вагон #" +
    carIdStr + " Место #" + seatIdStr;
}