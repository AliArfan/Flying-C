#ifndef FLIGHTFARE_H
#define FLIGHTFARE_H

#include <QString>

namespace Model {

    enum TravelClass {
        Economy,
        Business,
        FirstClass
    };

    struct FareInfo {
        const QString   travelClassType;
        const uint      maxBaggageWeight;
    };

    class FlightFare {
        const uint          id;
        const TravelClass   travelClass;
        const uint          priceAdult;
        const uint          priceChild;
        const uint          priceInfant;

    public:
        FlightFare(TravelClass travelClass, uint priceAdult);

        uint        getId();
        TravelClass getTravelClass();
        uint        getPriceAdult();
        uint        getPriceChild();
        uint        getPriceBaby();
        FareInfo    getFareInfo();
    };

}


#endif // FLIGHTFARE_H
