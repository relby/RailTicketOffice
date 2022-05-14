#include <cstddef>
#include <iostream>
#include <cstdint>
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <ctime>
#include <vector>
#include <utility>
#include "Ticket.h"
#include "GorkyRailway.h"

class RailTicketOffice {
private:
    GorkyRailway railway;
    std::vector<Ticket> tickets;

    bool CheckNotBought(std::tm date, Train* train, Car* car, Seat* seat) {
        for (auto ticket : tickets) {
            if (checkEqualTM(ticket.GetDate(), date) && ticket.GetTrain() == train && ticket.GetCar() == car && ticket.GetSeat() == seat) {
                return false;
            }
        }
        return true;
    }
public:
    RailTicketOffice() : railway(GorkyRailway(2, 2, 2)), tickets(std::vector<Ticket>()) {}

    std::vector<Ticket> BuyTickets(uint16_t ticketsAmount) {
        /*
            date - should be a string from "01/01" to "31/12"
        */
        std::vector<Ticket> out;
        for (uint16_t i = 0; i < ticketsAmount; i++) {
            std::cout << "Ticket #" << i + 1 << '\n';
            std::string buyerName = input<std::string>("Enter your name");
            std::string dateStr = input<std::string>("Enter the date");
            std::tm* date = parseDate(dateStr);
            while (date == nullptr) {
                auto dateRange = getDateRange();
                std::cout << "DATE SHOULD BE A STRING FROM `" << dateRange.first << "` TO `" << dateRange.second << "`\n";
                dateStr = input<std::string>("Enter the date");
                date = parseDate(dateStr);
            }
            TrainType trainType = chooseTrain();
            Train* train = railway.GetTrain(trainType);
            while (train == nullptr) {
                std::cout << "THERE IS NO TRAIN OF THIS TYPE\n";
                trainType = chooseTrain();
                train = railway.GetTrain(trainType);
            }
            uint16_t idOfCar = input<uint16_t>("Enter id of the car");
            Car* car = train->GetCar(idOfCar);
            while (car == nullptr) {
                std::cout << "THERE IS NO CAR WITH THIS ID\n";
                idOfCar = input<uint16_t>("Enter id of the car");
                car = train->GetCar(idOfCar);
            }
            uint16_t idOfSeat = input<uint16_t>("Enter id of the seat");
            Seat* seat = car->GetSeat(idOfSeat);
            while (seat == nullptr) {
                std::cout << "THERE IS NO SEAT WITH THIS ID\n";
                idOfSeat = input<uint16_t>("Enter id of the seat");
                seat = car->GetSeat(idOfSeat);
            }
            while (seat->IsBought()) {
                std::cout << "THIS SEAT HAS ALREADY BEEN BOUGHT\n";
                idOfSeat = input<uint16_t>("Enter id of the seat");
                seat = car->GetSeat(idOfSeat);
            }
            while (seat->IsReserved()) {
                std::cout << "THIS SEAT IS RESERVED\n";
                idOfSeat = input<uint16_t>("Enter id of the seat");
                seat = car->GetSeat(idOfSeat);
            }
            std::string details = generateTicketDetails(trainType, train->GetId(), car->GetType(), car->GetId(), seat->GetId());
            Ticket ticket = Ticket(*date, buyerName, train, car, seat);
            tickets.push_back(ticket);
            out.push_back(ticket);
        }
        return out;
    }

    bool CheckSeat() {
        std::string dateStr = input<std::string>("Enter the date");
        std::tm* date = parseDate(dateStr);
        if (date == nullptr) {
            auto dateRange = getDateRange();
            std::cout << "DATE SHOULD BE A STRING FROM `" << dateRange.first << "` TO `" << dateRange.second << "`\n";
            return nullptr;
        }
        TrainType trainType = chooseTrain();
        Train* train = railway.GetTrain(trainType);
        if (train == nullptr) {
            std::cout << "THERE IS NO TRAIN OF THIS TYPE\n";
            return nullptr;
        }
        uint16_t idOfCar = input<uint16_t>("Enter id of the car");
        Car* car = train->GetCar(idOfCar);
        if (car == nullptr) {
            std::cout << "THERE IS NO CAR WITH THIS ID\n";
            return nullptr;
        }
        uint16_t idOfSeat = input<uint16_t>("Enter id of the seat");
        Seat* seat = car->GetSeat(idOfSeat);
        if (seat == nullptr) {
            std::cout << "THERE IS NO SEAT WITH THIS ID\n";
            return nullptr;
        }
        return CheckNotBought(*date, train, car, seat);
    }

    std::vector<Ticket> GetTicketsByName(std::string buyerName) {
        std::vector<Ticket> out;
        for (auto ticket : tickets) {
            if (ticket.GetOwner() == buyerName) {
                out.push_back(ticket);
            }
        }
        return out;
    }

    void CancelTickets(std::string buyerName) {
        for (auto ticket : tickets) {
            if (ticket.GetOwner() == buyerName) {
                // TODO: deletion
            }
        }
    }
};

int main() {
    using namespace std;
    RailTicketOffice rto = RailTicketOffice();
    bool quit = false;
    while (!quit) {
        uint16_t operation = chooseOperation();
        switch (operation) {
        case 0: {
            uint16_t ticketsAmount = input<uint16_t>("Enter amount of tickets");
            vector<Ticket> tickets = rto.BuyTickets(ticketsAmount);
            if (tickets.empty()) {
                std::cout << "You haven't bought any tickets lol\n";
                continue;
            }
            std::cout << "Here is your tickets:\n";
            for (size_t i = 0; i < tickets.size(); i++) {
                Ticket ticket = tickets[i];
                cout << "  #" << i+1 << " " << tmToString(ticket.GetDate()) << " " << ticket.GetDetails() << '\n';
            }
            break;
        }
        case 1: {
            Seat* seat = rto.CheckSeat();
            if (seat == nullptr) {
                cout << "Couldn't get a seat\n";
                continue;
            }
            break;
        }
        case 2: {
            std::string buyerName = input<std::string>("Enter your name");
            std::vector<Ticket> tickets = rto.GetTicketsByName(buyerName);
            if (tickets.empty()) {
                cout << "No tickets found with that name\n";
                continue;
            }
            cout << tickets[0].GetOwner() << " has " << tickets.size() << " tickets:\n";
            for (size_t i = 0; i < tickets.size(); i++) {
                Ticket ticket = tickets[i];
                cout << "  #" << i+1 << " " << tmToString(ticket.GetDate()) << " " << ticket.GetDetails() << '\n';
            }
            break;
        }
        case 3:
            quit = true;
        }
    }
}