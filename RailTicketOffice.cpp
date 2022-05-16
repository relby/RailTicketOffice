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

    Train* chooseTrain(std::vector<Train*> trains) {
        std::cout << "Available Trains:\n";
        for (size_t i = 0; i < trains.size(); i++) {
            Train* train = trains[i];
            std::cout << "[" << i << "]: #" << train->GetId() << " " << trainTypeToString(train->GetType()) << '\n';
        }
        uint16_t input = -1;
        while (input >= trains.size()) {
            std::cin >> input;
        }
        return trains[input];
    }

    Car* chooseCar(std::vector<Car*> cars) {
        std::cout << "Available Cars:\n";
        for (size_t i = 0; i < cars.size(); i++) {
            Car* car = cars[i];
            std::cout << "[" << i << "]: #" << car->GetId() << " " << carTypeToString(car->GetType()) << '\n';
        }
        uint16_t input = -1;
        while (input >= cars.size()) {
            std::cin >> input;
        }
        return cars[input];
    }

    Seat* chooseSeat(std::tm date, Train* train, Car* car, std::vector<Seat*> seats) {
        std::cout << "Available Seats:\n";
        std::vector<Seat*> available_seats;
        for (Seat* seat : seats) {
            if (CheckTicket(date, train, car, seat) == nullptr) { // If there is no ticket
                available_seats.push_back(seat);
            }
        }
        for (size_t i = 0; i < available_seats.size(); i++) {
            Seat* seat = available_seats[i];
            std::cout << "[" << i << "]: #" << seat->GetId() << " " << seatTypeToString(seat->GetType()) << " " << generatePrice(car->GetType(), seat->GetType()) << "P\n";
        }
        uint16_t input = -1;
        while (input >= available_seats.size()) {
            std::cin >> input;
        }
        return available_seats[input];
    }

public:
    RailTicketOffice() : railway(GorkyRailway(2, 2, 2)), tickets(std::vector<Ticket*>()) {}

    std::vector<Ticket*> BuyTickets() {
        /*
            date - should be a string from "01/01" to "31/12"
        */
        uint16_t ticketsAmount = input<uint16_t>("Enter amount of tickets that you want to buy");
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
            TrainType trainType = chooseTrainType();
            std::vector<Train*> trains = railway.GetTrainsOfType(trainType);
            assert(!trains.empty());
            Train* train = chooseTrain(trains);

            CarType carType = chooseCarType(train->GetCarsTypes());

            std::vector<Car*> cars = train->GetCarsOfType(carType);
            assert(!cars.empty());

            Car* car = chooseCar(cars);

            std::vector<Seat*> seats = car->GetSeats();
            assert(!seats.empty());
            Seat* seat = chooseSeat(*date, train, car, seats);
            Ticket* ticket = new Ticket(BuyTicket, *date, buyerName, train, car, seat);
            tickets.push_back(ticket);
            out.push_back(ticket);
        }
        return out;
    }

    std::vector<Ticket*> ReserveTickets() {
        uint16_t ticketsAmount = input<uint16_t>("Enter amount of tickets that you want to reserve");
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
            TrainType trainType = chooseTrainType();
            std::vector<Train*> trains = railway.GetTrainsOfType(trainType);
            assert(!trains.empty());
            Train* train = chooseTrain(trains);

            CarType carType = chooseCarType(train->GetCarsTypes());

            std::vector<Car*> cars = train->GetCarsOfType(carType);
            assert(!cars.empty());

            Car* car = chooseCar(cars);

            std::vector<Seat*> seats = car->GetSeats();
            assert(!seats.empty());
            Seat* seat = chooseSeat(*date, train, car, seats);
            Ticket* ticket = new Ticket(ReserveTicket, *date, buyerName, train, car, seat);
            tickets.push_back(ticket);
            out.push_back(ticket);
        }
        return out;
    }

    void CheckAvailableSeats() {
        std::string dateStr = input<std::string>("Enter the date");
        std::tm* date = parseDate(dateStr);
        while (date == nullptr) {
            auto dateRange = getDateRange();
            std::cout << "DATE SHOULD BE A STRING FROM `" << dateRange.first << "` TO `" << dateRange.second << "`\n";
            dateStr = input<std::string>("Enter the date");
            date = parseDate(dateStr);
        }
        TrainType trainType = chooseTrainType();
        std::vector<Train*> trains = railway.GetTrainsOfType(trainType);
        assert(!trains.empty());
        Train* train = chooseTrain(trains);
        CarType carType = chooseCarType(train->GetCarsTypes());

        std::vector<Car*> cars = train->GetCarsOfType(carType);
        assert(!cars.empty());

        Car* car = chooseCar(cars);

        std::vector<Seat*> seats = car->GetSeats();
        assert(!seats.empty());
        std::vector<Seat*> available_seats;
        std::cout << "Available seats:\n";
        for (Seat* seat : seats) {
            if (CheckTicket(*date, train, car, seat) == nullptr) { // If there is no ticket
                available_seats.push_back(seat);
            }
        }
        for (size_t i = 0; i < available_seats.size(); i++) {
            Seat* seat = available_seats[i];
            std::cout << "[" << i << "]: #" << seat->GetId() << " " << seatTypeToString(seat->GetType()) << " " << generatePrice(car->GetType(), seat->GetType()) << "P\n";
        }
    }

    std::vector<Ticket*> GetTicketsByName() {
        std::string buyerName = input<std::string>("Enter your name");
        std::vector<Ticket*> out;
        for (auto ticket : tickets) {
            if (ticket->GetOwner() == buyerName) {
                out.push_back(ticket);
            }
        }
        return out;
    }

    std::vector<Ticket*> CancelTickets() {
        std::string buyerName = input<std::string>("Enter your name");
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
            vector<Ticket*> tickets = rto.BuyTickets();
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
            vector<Ticket*> tickets = rto.ReserveTickets();
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
            rto.CheckAvailableSeats();
            break;
        }
        case 3: { // Get Tickets by name
            std::vector<Ticket*> tickets = rto.GetTicketsByName();
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
            uint16_t sumPrice = 0;
            cout << tickets[0]->GetOwner() << " has " << tickets.size() << " tickets:\n";
            if (!boughtTickets.empty()) {
                cout << "  Your bought tickets:\n";
                for (size_t i = 0; i < boughtTickets.size(); i++) {
                    Ticket* ticket = tickets[i];
                    cout << "    #" << i+1 << " " << ticket->GetPrice()<< "Р " << tmToString(ticket->GetDate()) << " " << ticket->GetDetails() << '\n';
                    sumPrice += ticket->GetPrice();
                }
            }
            if (!reservedTickets.empty()) {
                cout << "  Your reserved tickets:\n";
                for (size_t i = 0; i < reservedTickets.size(); i++) {
                    Ticket* ticket = tickets[i];
                    cout << "    #" << i+1 << " " << ticket->GetPrice()<< "Р " << tmToString(ticket->GetDate()) << " " << ticket->GetDetails() << '\n';
                    sumPrice += ticket->GetPrice();
                }
            }
            cout << "Total price: " << sumPrice << '\n';
            break;
        }
        case 4: { // Cancel Tickets
            std::vector<Ticket*> canceledTickets = rto.CancelTickets();
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