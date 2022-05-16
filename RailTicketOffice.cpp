#include "RailTicketOffice.h"

Ticket* RailTicketOffice::CheckTicket(std::tm date, Train* train, Car* car, Seat* seat) {
    for (auto ticket : tickets) {
        if (checkEqualTM(ticket->GetDate(), date) && ticket->GetTrain() == train && ticket->GetCar() == car && ticket->GetSeat() == seat) {
            return ticket;
        }
    }
    return nullptr;
}

Train* RailTicketOffice::chooseTrain(std::vector<Train*> trains) {
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

Car* RailTicketOffice::chooseCar(std::vector<Car*> cars) {
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

Seat* RailTicketOffice::chooseSeat(std::tm date, Train* train, Car* car, std::vector<Seat*> seats) {
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

RailTicketOffice::RailTicketOffice(uint16_t numberOfLastochka, uint16_t numberOfFirmenniy, uint16_t numberOfSkoriy) : railway(GorkyRailway(numberOfLastochka, numberOfFirmenniy, numberOfSkoriy)), tickets(std::vector<Ticket*>()) {}

std::vector<Ticket*> RailTicketOffice::BuyTickets() {
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

std::vector<Ticket*> RailTicketOffice::ReserveTickets() {
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

void RailTicketOffice::CheckAvailableSeats() {
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

std::vector<Ticket*> RailTicketOffice::GetTicketsByName() {
    std::string buyerName = input<std::string>("Enter your name");
    std::vector<Ticket*> out;
    for (auto ticket : tickets) {
        if (ticket->GetOwner() == buyerName) {
            out.push_back(ticket);
        }
    }
    return out;
}

std::vector<Ticket*> RailTicketOffice::CancelTickets() {
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