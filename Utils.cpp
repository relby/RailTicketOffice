#include "Utils.h"

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
    return "";
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
    return "";
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
        std::tm* date = std::localtime(&t);
        if (day == date->tm_mday && month == (date->tm_mon + 1)) {
            return std::localtime(&t);
        }
        t += 60 * 60 * 24; // adding one day to the current time
    }
    return nullptr;
}
