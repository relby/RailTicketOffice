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
    std::vector<Ticket*> tickets;

    Ticket* CheckTicket(std::tm date, Train* train, Car* car, Seat* seat) {
        for (auto ticket : tickets) {
            if (checkEqualTM(ticket->GetDate(), date) && ticket->GetTrain() == train && ticket->GetCar() == car && ticket->GetSeat() == seat) {
                return ticket;
            }
        }
        return nullptr;
    }
public:
    RailTicketOffice() : railway(GorkyRailway(2, 2, 2)), tickets(std::vector<Ticket*>()) {}

    std::vector<Ticket*> BuyTickets(uint16_t ticketsAmount) {
        /*
            date - should be a string from "01/01" to "31/12"
        */
        std::vector<Ticket*> out;
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
            Ticket* ticket = new Ticket(BuyTicket, *date, buyerName, train, car, seat);
            tickets.push_back(ticket);
            out.push_back(ticket);
        }
        return out;
    }

    std::vector<Ticket*> ReserveTickets(uint16_t ticketsAmount) {
        std::vector<Ticket*> out;
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
            Ticket* ticket = new Ticket(ReserveTicket, *date, buyerName, train, car, seat);
            tickets.push_back(ticket);
            out.push_back(ticket);
        }
        return out;
    }

    Ticket* CheckSeat() {
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
        return CheckTicket(*date, train, car, seat);
    }

    std::vector<Ticket*> GetTicketsByName(std::string buyerName) {
        std::vector<Ticket*> out;
        for (auto ticket : tickets) {
            if (ticket->GetOwner() == buyerName) {
                out.push_back(ticket);
            }
        }
        return out;
    }

    std::vector<Ticket*> CancelTickets(std::string buyerName) {
        std::vector<Ticket*> out;
        for (auto it = tickets.begin(); it != tickets.end(); ) {
            if ((*it)->GetOwner() == buyerName) {
                out.push_back(*it);
                delete *it;
                it = tickets.erase(it);
            } else {
                ++it;
            }
        }
        return out;
    }
};

int main() {
    using namespace std;
    RailTicketOffice rto = RailTicketOffice();
    bool quit = false;
    while (!quit) {
        uint16_t operation = chooseOperation();
        switch (operation) {
        case 0: { // Buy Tickets
            uint16_t ticketsAmount = input<uint16_t>("Enter amount of tickets that you want to buy");
            vector<Ticket*> tickets = rto.BuyTickets(ticketsAmount);
            if (tickets.empty()) {
                std::cout << "You haven't bought any tickets lol\n";
                continue;
            }
            std::cout << "You successfully bought " << tickets.size() << " tickets:\n";
            for (size_t i = 0; i < tickets.size(); i++) {
                Ticket* ticket = tickets[i];
                cout << "    #" << i+1 << " " << ticket->GetPrice()<< "Р " << tmToString(ticket->GetDate()) << " " << ticket->GetDetails() << '\n';
            }
            break;
        }
        case 1: { // Reserve Tickets
            uint16_t ticketsAmount = input<uint16_t>("Enter amount of tickets that you want to reserve");
            vector<Ticket*> tickets = rto.ReserveTickets(ticketsAmount);
            if (tickets.empty()) {
                std::cout << "You haven't reserve any tickets lol\n";
                continue;
            }
            std::cout << "You successfully reserved " << tickets.size() << " tickets:\n";
            for (size_t i = 0; i < tickets.size(); i++) {
                Ticket* ticket = tickets[i];
                cout << "    #" << i+1 << " " << ticket->GetPrice()<< "Р " << tmToString(ticket->GetDate()) << " " << ticket->GetDetails() << '\n';
            }
            break;
        }
        case 2: { // Check Seat
            Ticket* ticket = rto.CheckSeat();
            if (ticket == nullptr) {
                cout << "You can buy this seat\n";
                continue;
            }
            switch (ticket->GetType()) {
            case BuyTicket:
                cout << "This seat is bought\n";
                break;
            case ReserveTicket:
                cout << "This seat is reserved\n";
                break;
            }
            break;
        }
        case 3: { // Get Tickets by name
            std::string buyerName = input<std::string>("Enter your name");
            std::vector<Ticket*> tickets = rto.GetTicketsByName(buyerName);
            if (tickets.empty()) {
                cout << "No tickets found with that name\n";
                continue;
            }
            std::vector<Ticket*> boughtTickets, reservedTickets;
            for (Ticket* ticket : tickets) {
                if (ticket->GetType() == BuyTicket) {
                    boughtTickets.push_back(ticket);
                } else if (ticket->GetType() == ReserveTicket) {
                    reservedTickets.push_back(ticket);
                }
            }
            cout << tickets[0]->GetOwner() << " has " << tickets.size() << " tickets:\n";
            if (!boughtTickets.empty()) {
                cout << "  Your bought tickets:\n";
                for (size_t i = 0; i < boughtTickets.size(); i++) {
                    Ticket* ticket = tickets[i];
                    cout << "    #" << i+1 << " " << ticket->GetPrice()<< "Р " << tmToString(ticket->GetDate()) << " " << ticket->GetDetails() << '\n';
                }
            }
            if (!reservedTickets.empty()) {
                cout << "  Your reserved tickets:\n";
                for (size_t i = 0; i < reservedTickets.size(); i++) {
                    Ticket* ticket = tickets[i];
                    cout << "    #" << i+1 << " " << ticket->GetPrice()<< "Р " << tmToString(ticket->GetDate()) << " " << ticket->GetDetails() << '\n';
                }
            }
            break;
        }
        case 4: { // Cancel Tickets
            std::string buyerName = input<std::string>("Enter your name");
            std::vector<Ticket*> canceledTickets = rto.CancelTickets(buyerName);
            if (canceledTickets.empty()) {
                cout << "You don't have any tickets!\n";
                continue;
            }
            cout << "You canceled " << canceledTickets.size() << " tickets:\n";
            for (size_t i = 0; i < canceledTickets.size(); i++) {
                Ticket* ticket = canceledTickets[i];
                cout << "    #" << i+1 << " " << ticket->GetPrice()<< "Р " << tmToString(ticket->GetDate()) << " " << ticket->GetDetails() << '\n';
            }
            break;
        }
        case 5:
            quit = true;
        }
    }
}