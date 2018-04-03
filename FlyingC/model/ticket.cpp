#include "ticket.h"


using namespace std;

namespace Model {
    /*
        Stores the information about the ticket: the  booking code, the flight id, the first and last name of the ticket owner as well as the prive and which travel class.
    */

    static uint uniqueTicketId{ 1000000 };

    Ticket::Ticket(QString bookingCode, uint flightId,  QString     firstname,
                   QString lastname,    uint price,     TravelClass ticketClass) :
        id          { uniqueTicketId },
        bookingCode { bookingCode },
        flightId    { flightId },
        firstname   { firstname },
        lastname    { lastname },
        price       { price },
        ticketClass { ticketClass } {

        if(bookingCode.isEmpty())
            throw invalid_argument("Booking code must be specified.");
        if(flightId < 1)
            throw invalid_argument("FlightId cannot be 0.");
        if(firstname.isEmpty())
            throw invalid_argument("Firstname must be specified.");
        if(lastname.isEmpty())
            throw invalid_argument("Lastname must be specified.");

        uniqueTicketId++;
    }

    uint Ticket::getId(){
        return id;
    }

    QString Ticket::getFirstname(){
        return firstname;
    }

    QString Ticket::getLastname() {
        return lastname;
    }

    uint Ticket::getPrice() {
        return price;
    }

    TravelClass Ticket::getTicketClass() {
        return ticketClass;
    }

    bool Ticket::isCanceled(){
        return canceled;
    }

}
