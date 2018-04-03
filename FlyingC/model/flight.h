#ifndef FLIGHT_H
#define FLIGHT_H

#include <QDateTime>
#include <QMap>
#include "model/aircraft.h"
#include "model/airport.h"
#include "model/flightfare.h"

namespace Model {

    uint estimateDistance(const Airport& origin, const Airport& destination);
    uint estimateTravelTime(int distance, int marchSpeed);

    class Flight {
        const uint          id;
        const Airport&      origin;
        const Airport&      destination;
        const QDateTime&    depature;
        const QDateTime&    arrival;
        const Aircraft&     aircraft;
        const uint          estimatedDistance;
        const uint          estimatedTravelTime;

        QMap<TravelClass, FlightFare*> flightFares;

    public:
        Flight(Aircraft& aircraft, Airport& origin, Airport& destination, QDateTime& depature, QDateTime& arrival);

        uint                getId();
        QString             getFlightNumber();
        Airport             getOrigin();
        Airport             getDestination();
        QDateTime           getDepature();
        QDateTime           getArrival();
        uint                getEstimatedDistance();
        uint                getEstimatedTravelTime();
        const Aircraft&     getAircraft();
        void                addFlightFare(FlightFare* flightFare);
        void                addFlightFare(std::initializer_list<FlightFare*> flightFares);
        QMap<TravelClass, FlightFare*>  getFlightFare();
    };

}


#endif // FLIGHT_H
