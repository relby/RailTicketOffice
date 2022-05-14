#pragma once
#include <string>
#include <ctime>

class Ticket {
private:
    std::string owner;
    std::tm date;
    std::string details;
public:
    Ticket();
    Ticket(std::string owner, std::tm date, std::string details);
};