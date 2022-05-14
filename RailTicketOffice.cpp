#include <cstddef>
#include <iostream>
#include <cstdint>
#include <stdlib.h>
#include <string>
#include <ctime>
#include <vector>
#include "Ticket.h"
#include "GorkyRailway.h"

class RailTicketOffice {
private:
    GorkyRailway railway;
    std::vector<Ticket*> tickets;
public:
    RailTicketOffice() : railway(GorkyRailway(2, 2, 2)), tickets(std::vector<Ticket*>()) {}

    Ticket BuyTicket(TrainType trainType, uint16_t idOfCar, uint16_t idOfSeat, std::string dateStr, std::string buyerName) {
        /*
            date - should be a string from "01/01" to "31/12"
        */
        std::tm* date = parseDate(dateStr);
        if (date == nullptr) {
            std::cout << "BAD DATE\n";
        }
        Train* train = railway.GetTrain(trainType);
        if (train == nullptr) {
            std::cout << "THERE IS NO TRAIN OF THIS TYPE\n";
        }
        Car* car = train->GetCar(idOfCar);
        if (car == nullptr) {
            std::cout << "THERE IS NO CAR WITH THIS ID\n";
        }
        Seat* seat = car->GetSeat(idOfSeat);
        if (seat == nullptr) {
            std::cout << "THERE IS NO SEAT WITH THIS ID\n";
        }
        if (seat->IsBought()) {
            std::cout << "THIS SEAT HAS ALREADY BEEN BOUGHT\n";
        }
        if (seat->IsReserved()) {
            std::cout << "THIS SEAT IS RESERVED\n";
        }
        return seat->BuyTicket(*date, buyerName);
    }

    bool CheckSeat(TrainType trainType, uint16_t idOfCar, uint16_t idOfSeat) {
        Train* train = railway.GetTrain(trainType);
        if (train == nullptr) {
            std::cout << "THERE IS NO TRAIN OF THIS TYPE\n";
            return false;
        }
        Car* car = train->GetCar(idOfCar);
        if (car == nullptr) {
            std::cout << "THERE IS NO CAR WITH THIS ID\n";
            return false;
        }
        Seat* seat = car->GetSeat(idOfSeat);
        if (seat == nullptr) {
            std::cout << "THERE IS NO SEAT WITH THIS ID\n";
            return false;
        }
        return !seat->IsBought();
    }
};

int main() {
    RailTicketOffice().CheckSeat(LastochkaType, 1, 3);
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    std::string date_str;
    std::cin >> date_str;
    std::tm* date = parseDate(date_str);
    if (date != nullptr) {
        std::cout << date->tm_mday << ' ' << (date->tm_mon + 1) << '\n';
    } else {
        std::cout << "bad date\n";
    }
}