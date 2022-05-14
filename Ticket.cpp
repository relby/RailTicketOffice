#include "Ticket.h"

Ticket::Ticket() {}
Ticket::Ticket(std::string owner, std::tm date, std::string details) : owner(owner), date(date), details(details) {}