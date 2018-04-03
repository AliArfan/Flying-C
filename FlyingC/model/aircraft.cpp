#include "aircraft.h"

using namespace std;

namespace Model {
    /*
     * Object of aircraft. Holds the inofrmation about the aircraft model, travel speed, and which kind of travel classes the aircraft has to offer.
     */

    // the aircraft id.
    static uint uniqueAircraftId{ 1 };

    Aircraft::Aircraft(QString model, uint marchSpeed, double pricePrKm, bool firstClass, bool businessClass, bool economyClass) :
        id          { uniqueAircraftId },
        model       { model },
        marchSpeed  { marchSpeed },
        pricePrKm   { pricePrKm } {

        constexpr uint MIN_MARCH_SPEED { 100 };

        //Error checking: a model for the aircraft must be specified.
        if(model.isEmpty())
            throw invalid_argument("Aircraft model cannot be empty.");
        //the marchspeed must be higher than given minium march speed.
        if(marchSpeed <= MIN_MARCH_SPEED)
            throw invalid_argument("March speed must be greater than " + to_string(MIN_MARCH_SPEED ) + " km/h.");
        //Operation cost for the aircraft.
        if(pricePrKm <= 0)
            throw invalid_argument("Operation cost must be greater than 0.");

        try {
            setAccommodation(firstClass, businessClass, economyClass);
        } catch(...) {
            throw;
        }

        uniqueAircraftId++;
    }

    uint Aircraft::getId() const {
        return id;
    }

    QString Aircraft::getModel() const {
        return model;
    }

    uint Aircraft::getMarchSpeed() const {
        return marchSpeed;
    }

    double Aircraft::getPricePrKm() const {
        return pricePrKm;
    }

    qint8 Aircraft::getClass() const {
        return (economyClass? 1:0) | (businessClass? 2:0) | (firstClass? 4:0);
    }

    bool Aircraft::hasFirstClass() const {
        return firstClass;
    }

    bool Aircraft::hasBusinessClass() const {
        return businessClass;
    }

    bool Aircraft::hasEconomyClass() const {
        return economyClass;
    }
    //sets the accomendation for the aircraft.
    void Aircraft::setAccommodation(bool firstClass, bool businessClass, bool economyClass) {
        if(!(firstClass | businessClass | economyClass))
            throw invalid_argument("Aircraft must have at least one accommodation.");

        this->firstClass    = firstClass;
        this->businessClass = businessClass;
        this->economyClass  = economyClass;
    }



}
