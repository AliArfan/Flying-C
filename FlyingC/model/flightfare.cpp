#include "flightfare.h"

using namespace std;

namespace Model {
    /*
     * Stores hte information about the flightfares according to which travel class you are flying with.
     */


    /*
     * Defined outside class and in source file means these variables will only be accessable
     * whitin this scope.
     */
    static constexpr double     priceFactorChild { 0.5 };
    static constexpr double     priceFactorInfant{ 0.1 };
    static const FareInfo   fareInfo[3] {
        { "Economy",        30 },
        { "Business",       40 },
        { "First-class",    50 }
    };

    static uint uniqueFlightFareId{ 0 };

    FlightFare::FlightFare(TravelClass travelClass, uint priceAdult) :
        id          { uniqueFlightFareId },
        travelClass { travelClass },
        priceAdult  { priceAdult },
        priceChild  { (uint)(priceAdult * priceFactorChild) },
        priceInfant { (uint)(priceAdult * priceFactorInfant) } {

        if(priceAdult < 1)
            throw invalid_argument("Flight fare for adults must be greater than 0.");

        uniqueFlightFareId++;
    }

    uint FlightFare::getId() {
        return id;
    }

    TravelClass FlightFare::getTravelClass() {
        return travelClass;
    }

    uint FlightFare::getPriceAdult() {
        return priceAdult;
    }

    uint FlightFare::getPriceChild() {
        return priceChild;
    }

    uint FlightFare::getPriceBaby() {
        return priceInfant;
    }

    FareInfo FlightFare::getFareInfo() {
        return fareInfo[travelClass];
    }

}
