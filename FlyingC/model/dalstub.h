#ifndef DATAACCESSSTUB_H
#define DATAACCESSSTUB_H

#include <QMap>
#include "idal.h"

/*
 * The data access stub creates our fictive data.
*/

namespace DAL {

    class DataAccessStub : public IDataAccess {

        QVector<Aircraft*>  aircrafts;
        QVector<Airport*>   airports;
        QMap<QString, Booking*> bookedFlights;

        QFlightMap flights;

        DataAccessStub();
        void generateMockFlights(QDate* date);
        void generateMockPrice(uint distance, Flight* flight);
    public:
        Airport*                getAirport(QString iataCode) const override;
        QVector<Airport*>       getAllAirports() const override;
        QFlightMap              getAllFlights() const override;
        QVector<Flight*>*       findFlight(QString fromAirport, QString toAirport, QDate departureDate) const override;
        QString generateUniqueBookingcode() const override;
        void addBooking(Booking* booking) override;
        Booking* getBooking(QString code) const override;
        static DataAccessStub*  getInstance();
    };
}

#endif // DATAACCESSSTUB_H
