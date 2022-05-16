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

    Ticket* CheckTicket(std::tm date, Train* train, Car* car, Seat* seat);
    Train* chooseTrain(std::vector<Train*> trains);
    Car* chooseCar(std::vector<Car*> cars);
    Seat* chooseSeat(std::tm date, Train* train, Car* car, std::vector<Seat*> seats);
public:
    RailTicketOffice(uint16_t numberOfLastochka, uint16_t numberOfFirmenniy, uint16_t numberOfSkoriy);

    std::vector<Ticket*> BuyTickets();
    std::vector<Ticket*> ReserveTickets();
    void CheckAvailableSeats();
    std::vector<Ticket*> GetTicketsByName();
    std::vector<Ticket*> CancelTickets();
    ~RailTicketOffice();
};