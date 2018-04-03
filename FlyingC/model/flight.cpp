#include "flight.h"
#include <math.h>

using namespace std;

namespace Model {

    static uint uniqueFlightId{ 1 };

    /*
         * Stores the information about the flight. From one airport to another, tgoether with the depature and arrival time.

        */

    /*
         * This functiion uses the Haversine forumla to calculate the distance
         * between to coordinates using their latitude and longitude position.
         *
         * https://en.wikipedia.org/wiki/Haversine_formula
        */
    uint estimateDistance(const Airport& origin, const Airport& destination) {
        constexpr double    pi { 3.141592653589793 };
        constexpr double    earthRadius { 6371 };
        const double        p1 { origin.getLatitude() * (pi / 180) };
        const double        p2 { destination.getLatitude() * (pi / 180) };
        const double        deltaY { (destination.getLatitude() - origin.getLatitude()) * (pi / 180) };
        const double        deltaX { (destination.getLongitude() - origin.getLongitude()) * (pi / 180) };

        const double        a {
            sin(deltaY / 2) * sin(deltaY / 2) +
                    cos(p1) * cos(p2) *
                    sin(deltaX / 2) * sin(deltaX / 2)
        };

        const double        c { 2 * atan2(sqrt(a), sqrt(1 - a)) };

        return (int)(earthRadius * c);
    }

    uint estimateTravelTime(int distance, int marchSpeed) {
        constexpr int hoursToSeconds { 3600 };
        const double hours { distance / (double)marchSpeed };
        return hours * hoursToSeconds;
    }

    QString Flight::getFlightNumber() {
        int     t[3]        { depature.time().hour(), depature.time().second(), arrival.time().hour() };
        uint    n           { aircraft.getId() };
        QString flightNumber{ "FLY" };

        for(int i = 0; i < 3; i++) {
            n += (uint)origin.getIataCode().at(i).toLatin1() + (uint)destination.getIataCode().at(i).toLatin1();
            n = (n + (uint)t[i]) % 10;
            flightNumber.append(QString::number(n));
        }
        return flightNumber;
    }

    Flight::Flight(Aircraft&  aircraft, Airport &origin, Airport &destination, QDateTime& depature, QDateTime& arrival) :
        id                  { uniqueFlightId },
        origin              { origin },
        destination         { destination },
        depature            { depature },
        arrival             { arrival },
        aircraft            { aircraft },
        estimatedDistance   { estimateDistance(origin, destination) },
        estimatedTravelTime { estimateTravelTime(estimatedDistance, aircraft.getMarchSpeed()) } {

        if(depature >= arrival)
            throw invalid_argument("DateTime for arrival must be after depature.");

        // We subtract an error margin of 10%.
        depature.addSecs( (qint64) estimatedTravelTime * 0.90);
        if(depature >= arrival)
            throw invalid_argument("Arrival must be after " + depature.toString("dd.MM.yyyy hh:mm:ss").toStdString() + ".");

        uniqueFlightId++;
    }

    uint Flight::getId() {
        return id;
    }

    Airport Flight::getOrigin() {
        return origin;
    }

    Airport Flight::getDestination() {
        return destination;
    }

    QDateTime Flight::getDepature() {
        return depature;
    }

    QDateTime Flight::getArrival() {
        return arrival;
    }

    const Aircraft& Flight::getAircraft() {
        return aircraft;
    }

    uint Flight::getEstimatedDistance() {
        return estimatedDistance;
    }

    uint Flight::getEstimatedTravelTime() {
        return estimatedTravelTime;
    }

    void Flight::addFlightFare(FlightFare *flightFare) {
        flightFares.insert(flightFare->getTravelClass(), flightFare);
    }

    void Flight::addFlightFare(initializer_list<FlightFare *> flightFares) {
        for (FlightFare* fare : flightFares)
            addFlightFare(fare);
    }

    //returns the flightfares for this flight.
    QMap<TravelClass, FlightFare*>  Flight::getFlightFare(){
        return  flightFares;
    }

}
