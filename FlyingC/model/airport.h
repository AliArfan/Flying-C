#ifndef AIRPORT_H
#define AIRPORT_H

#include <QString>

namespace Model {

    class Airport {
        const uint      id;
        const QString   iataCode;   // iata code found from: https://en.wikipedia.org/wiki/IATA_airport_code
        const QString   name;
        const QString   city;
        const QString   country;
        const double    latitude;   // Breddegrad
        const double    longitude;  // Lengdegrad

    public:
        Airport(QString iataCode, QString name, QString city, QString country, double latitude, double longitude);

        uint    getId() const;
        QString getIataCode() const;
        QString getName() const;
        QString getLongName() const;
        QString getCity() const;
        QString getCountry() const;
        double  getLatitude() const;
        double  getLongitude() const;
        bool    compareIataCode(QString code) const;
    };

}


#endif // AIRPORT_H
