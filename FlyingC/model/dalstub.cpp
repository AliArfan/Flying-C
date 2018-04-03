#include "dalstub.h"
#include <QDebug>

namespace DAL {

    /*
        Our "model-controller": saves and returns the necessary information to operate the program such as the airport, the flights, aircrafts and the logic needed
        to operate the program.
    */

    void DataAccessStub::generateMockPrice(uint distance, Flight* flight) {
        constexpr double economy        { 1.20 };
        constexpr double business       { 2.50 };
        constexpr double firstClass     { 6.00 };

        const uint base { (uint)(distance * flight->getAircraft().getPricePrKm()) };

        for(qint8 accommodation = 1; accommodation <= 4; accommodation <<= 1) {
            switch (accommodation & flight->getAircraft().getClass()) {
            case 1:
                flight->addFlightFare(new FlightFare(TravelClass::Economy, base * economy));
                break;
            case 2:
                flight->addFlightFare(new FlightFare(TravelClass::Business, base * business));
                break;
            case 4:
                flight->addFlightFare(new FlightFare(TravelClass::FirstClass, base * firstClass));
                break;
            default:
                // The aircraft has no accommodation classes.
                break;
            }
        }
    }

    void DataAccessStub::generateMockFlights(QDate* date) {
        Airport*    origin      { nullptr };
        QDateTime*  departure   { nullptr };
        QDateTime*  arrival     { nullptr };
        Flight*     flight      { nullptr };
        uint        distance    { 0 };
        uint        travelTime  { 0 };

        QMap<QDate, QVector<Flight*>*>* departuresFromAirport { nullptr };
        QVector<Flight*>* departures { nullptr };

        for(int i = 0; i < airports.size(); i++) {
            // We take out the airport we want to generate flights from.
            origin = airports.takeFirst();

            // We look the airport up from our flights map.
            auto p = flights.find(origin->getIataCode());
            if(p == flights.end()) {
                // If the airport was not in our flights map, we must add it.
                departuresFromAirport = new QMap<QDate, QVector<Flight*>*>;
                flights.insert(origin->getIataCode(), departuresFromAirport);
            } else {
                departuresFromAirport = (*p);
            }

            // We create the vector which will hold all departures for this new date.
            departures = new QVector<Flight*>;
            departuresFromAirport->insert(*date, departures);

            // We iterate throught all the remaining airports and aircrafts.
            for(int j = 0; j < airports.size(); j++) {
                for(int n = 0; n < aircrafts.size(); n++) {
                    distance   = estimateDistance(*origin, *airports[j]);
                    travelTime = estimateTravelTime(distance, aircrafts[n]->getMarchSpeed());
                    // We create departurs every 2 hours.
                    for(int t = 0; t < 1; t+= 2 ) {
                        departure = new QDateTime(*date, QTime(6 + t,30,0,0), Qt::LocalTime);
                        arrival   = new QDateTime(departure->addSecs(travelTime));
                        flight    = new Flight(*aircrafts[n], *origin, *airports[j], *departure, *arrival);
                        generateMockPrice(distance, flight);
                        // We add the flight to the list.
                        departures->append(flight);
                    }
                }
            }

            // We put the airport we generated flights to, back in the flights map.
            airports.append(origin);
        }
    }

    DataAccessStub::DataAccessStub() {
        airports = {
            new Airport("OSL", "Gardermoen",    "Oslo",         "Norway",       60.202778,  11.083889),
            new Airport("SVG", "Sola",          "Stavanger",    "Norway",       58.880441,   5.631402),
            new Airport("BGO", "Flesland",      "Bergen",       "Norway",       60.291830,   5.222017),
            new Airport("TRD", "Værnes",        "Trondheim",    "Norway",       63.458270,  10.922599),
            new Airport("EVE", "Evenes",        "Harstad",      "Norway",       68.488596,  16.681443),
            new Airport("CPH", "Kastrup",       "Copenhagen",   "Denmark",      55.618023,  12.650762),
            new Airport("BKK", "Suvarnabhumi",  "Bangkok",      "Thailand",     13.692500, 100.750000),
            new Airport("SGN", "Tan Son Nhat",  "Ho Chi Minh",  "Vietnam",      10.818889, 106.651944),
            new Airport("FNJ", "Sunan",         "Pyongyang",    "North Korea",  39.200846, 125.676536),
            new Airport("HND", "Haneda",        "Tokyo",        "Japan",        35.553333, 139.781111)
        };

        aircrafts = {
            new Aircraft("Boeing 747-400",               933,   0.50,   true,   true,   true),
            new Aircraft("Boeing 777-300",               892,   0.62,   false,  true,   true),
            new Aircraft("Airbus A380-800",              860,   0.52,   true,   true,   true),
            new Aircraft("Airbus A350-900",              903,   0.59,   false,  true,   true),
            new Aircraft("Lockheed Martin F-22 Raptor", 2410,   40.0,   false,  false,  true),
            new Aircraft("AliLine 2000",                 169,   0.10,   true,   true ,  true)
        };

        QDate date { QDate::currentDate() };
        for(uint day = 0; day < 30; day++) {
            generateMockFlights(&date);
            date=date.addDays(1);
        }
    }

    Airport* DataAccessStub::getAirport(QString iataCode) const {
        for(auto p = airports.begin(); p != airports.end(); ++p)
            if(iataCode.compare((*p)->getIataCode()) == 0)
                return (*p);
        return nullptr;
    }

    QVector<Airport*> DataAccessStub::getAllAirports() const {
        return airports;
    }

    QFlightMap DataAccessStub::getAllFlights() const{
        return flights;
    }

    QVector<Flight*>* DataAccessStub::findFlight(QString fromAirport, QString toAirport, QDate departureDate) const {
        QVector<Flight*>* matches = new QVector<Flight*>;

        auto pAirport { flights.find(fromAirport) };
        if(pAirport != flights.end()) {
            auto pDepartures = (*pAirport)->find(departureDate);
            if(pDepartures != (*pAirport)->end())
                for(Flight* f : *(*pDepartures))
                    if(f->getDestination().compareIataCode(toAirport))
                        matches->append(f);
        }
        return matches;
    }

    DataAccessStub* DataAccessStub::getInstance() {
        static DataAccessStub* instance{ nullptr };
        if (!instance) {
            instance = new DataAccessStub();
        }
        return instance;
    }

    QString DataAccessStub::generateUniqueBookingcode() const{
        QString temp;

        // Generates a booking code through brute force
        // Collision chance is really low, so not an issue for this app
        do {
            temp = Booking::generateBookingcode();
        } while((bookedFlights.contains(temp)));

        return temp;
    }

    void DataAccessStub::addBooking(Booking* booking){
        bookedFlights.insert(booking->getBookingCode(),booking);
    }

    Booking* DataAccessStub::getBooking(QString code) const{
        return bookedFlights[code];
    }

}
