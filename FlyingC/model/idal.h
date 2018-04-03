#ifndef IDAL_H
#define IDAL_H

#include <QVector>
#include <QDebug>

#include "aircraft.h"
#include "airport.h"
#include "booking.h"
#include "flight.h"
#include "flightfare.h"
#include "ticket.h"
#include "session.h"

/*
 * The "data access layer interface" (DAL) to our "in memory db".
*/
using namespace Model;

namespace DAL {
    typedef QMap<QString, QMap<QDate, QVector<Flight*>*>*> QFlightMap;

    class IDataAccess {
    public:
        virtual Airport*            getAirport(QString iataCode) const = 0;
        virtual QVector<Airport*>   getAllAirports() const = 0;
        virtual QFlightMap          getAllFlights() const = 0;
        virtual QVector<Flight*>*   findFlight(QString fromAirport, QString toAirport, QDate departureDate) const = 0;
        virtual  QString generateUniqueBookingcode() const =0;
        virtual void addBooking(Booking* booking)  = 0;
        virtual Booking* getBooking(QString code) const =0;
    };
}

#endif // IDAL_H
