#include "airport.h"

using namespace std;

namespace Model {
    /*
     * Aiport object. Holds the information about one specifig airport. The name, city,country and its position.
     */
    static uint uniqueAirportId{ 1 };

    Airport::Airport(QString iataCode, QString name, QString city, QString country, double latitude, double longitude) :
        id          { uniqueAirportId },
        iataCode    { iataCode },
        name        { name },
        city        { city },
        country     { country },
        latitude    { latitude },
        longitude   { longitude } {

        // The IATA code only has three characters, no more and no less.

        if(iataCode.length() != 3)
            throw invalid_argument("Airport must have a three letter IATA code.");

        if(name.isEmpty())
            throw invalid_argument("Airport must have a name.");

        if(city.isEmpty())
            throw invalid_argument("Airport must have a city connection.");

        if(country.isEmpty())
            throw invalid_argument("Airport must have a country.");

        uniqueAirportId++;
    }

    uint Airport::getId() const {
        return id;
    }

    QString Airport::getIataCode() const {
        return iataCode;
    }

    QString Airport::getName() const {
        return name;
    }

    QString Airport::getLongName() const {
        return city + " - " + name;
    }

    QString Airport::getCity() const {
        return city;
    }

    QString Airport::getCountry() const {
        return country;
    }

    double Airport::getLatitude() const {
        return latitude;
    }

    double Airport::getLongitude() const {
        return longitude;
    }
    bool Airport::compareIataCode(QString code) const {
        return iataCode == code;

    }

}
