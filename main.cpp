#include "RailTicketOffice.h"

const uint16_t NUMBER_OF_LASTOCHKA = 2;
const uint16_t NUMBER_OF_FIRMENNIY = 2;
const uint16_t NUMBER_OF_SKORIY = 2;

int main() {
    RailTicketOffice rto = RailTicketOffice(NUMBER_OF_LASTOCHKA, NUMBER_OF_FIRMENNIY, NUMBER_OF_SKORIY);
    rto.StartOperations();
}