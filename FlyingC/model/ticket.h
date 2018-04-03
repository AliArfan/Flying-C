#ifndef TICKET_H
#define TICKET_H

#include <QString>
#include "flightfare.h"

namespace Model {

    class Ticket {
        const uint          id;
        const QString       bookingCode;
        const uint          flightId;
        const QString       firstname;
        const QString       lastname;
        const uint          price;
        const TravelClass   ticketClass;

        bool                canceled    { false };

    public:
        Ticket(QString bookingCode, uint flightId, QString firstname, QString lastname, uint price, TravelClass ticketClass);

        uint        getId();
        QString     getFirstname();
        QString     getLastname();
        uint        getPrice();
        TravelClass getTicketClass();
        bool        isCanceled();
    };

}


#endif // TICKET_H
