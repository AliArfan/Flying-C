#ifndef SESSION_H
#define SESSION_H

#include <QVector>
#include <QDate>
#include <QString>
#include "flight.h"

namespace  Model {

    struct Session {

        Session();

        struct Search {
            QString     fromAirport;
            QString     toAirport;
            bool        oneWay;
            QDate       fromDate;
            QDate       toDate;
            int         adultAmount;
            int         infantsAmount;
            int         kidsAmount;

            void validate();
        };

        struct ChosenJourney {
            Flight*     flightId{ nullptr };
            TravelClass travelClass;
        };

        struct Traveller {
            QString     ageGroup;
            QString     firstname;
            QString     lastname;
            QString     gender;
            QDate       birthofDate;

            void validate();
        };

        struct PaymentDetail {
            QString     cardType;
            QString     cardNumber;
            QString     cardHolder;
            QDate       expiryDate;
            QString     ccv;
            void validate();
        };

        const uint              id;

        Search                  search;
        ChosenJourney           journeyOut;
        ChosenJourney           journeyBack;
        QVector<Flight*>*       matchesOut      { nullptr };
        QVector<Flight*>*       matchesBack     { nullptr };
        QVector<Traveller*>*    travellers      { nullptr };
        PaymentDetail           paymentDetail;
        QString bookingReference;
    };

}

#endif // SESSION_H
