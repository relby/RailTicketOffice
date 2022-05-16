#include "RailTicketOffice.h"

const uint16_t NUMBER_OF_LASTOCHKA = 2;
const uint16_t NUMBER_OF_FIRMENNIY = 2;
const uint16_t NUMBER_OF_SKORIY = 2;

int main() {
    using namespace std;
    RailTicketOffice rto = RailTicketOffice(NUMBER_OF_LASTOCHKA, NUMBER_OF_FIRMENNIY, NUMBER_OF_SKORIY);
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