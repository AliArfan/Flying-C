#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <QString>

namespace Model {

    class Aircraft {
        const uint      id;
        const QString   model;
        const uint      marchSpeed;
        const double    pricePrKm;
        bool            firstClass      { false };
        bool            businessClass   { false };
        bool            economyClass    { false };

    public:
        Aircraft(QString model, uint marchSpeed, double pricePrKm, bool firstClass, bool businessClass, bool economyClass);

        uint    getId() const;
        QString getModel() const;
        uint    getMarchSpeed() const;
        double  getPricePrKm() const;
        qint8   getClass() const;
        bool    hasFirstClass() const;
        bool    hasBusinessClass() const;
        bool    hasEconomyClass() const;
        void    setAccommodation(bool firstClass, bool businessClass, bool economyClass);

    };

}


#endif // AIRCRAFT_H
