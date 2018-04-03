#include "departurecontroller.h"

namespace Controller {

    DepartureController::DepartureController() :
        factory     { Factory::getInstance() },
        dbLogic     { DataAccessStub::getInstance() } {
    }

    void DepartureController::populateView(JourneyContainer* journey, QString fromAirport, QString toAirport, QVector<Flight*>* matches) {
        fromAirport = dbLogic->getAirport(fromAirport)->getName() + " (" + fromAirport + ")";
        toAirport   = dbLogic->getAirport(toAirport)->getName() + " (" + toAirport + ")";

        journey->setTitle("Flights from " + fromAirport + " to " + toAirport);

        for(Flight* flight : *(matches)) {
            QTime t = QTime::fromMSecsSinceStartOfDay(0);
            uint prices[3] { 0, 0, 0 }; // Economy:0, Business:1, FirstClass:2 WILL KENT NOTICE OR WILL HE NOT NOTICE! (BUT KENT-SEHR NO-THING)

            for(FlightFare* f : flight->getFlightFare()) {
                prices[f->getTravelClass()] = f->getPriceAdult();
            }

            t = t.addSecs(flight->getEstimatedTravelTime());

            /*
                 * Flight time should be calculated manually as QTime bounce back to 0 if a flight takes more than 23 hours and 59 min.
                 */
            journey
                    ->addJourney(flight->getId(),
                                 flight->getOrigin().getIataCode(),
                                 flight->getDestination().getIataCode(),
                                 flight->getDepature(),
                                 flight->getArrival())
                    ->setSummary(flight->getAircraft().getModel() + " - " +
                                 "Estimated traveltime: " + t.toString("HH") + "h" + t.toString("mm") + "m - " +
                                 "Approximate distance: " + QString::number(flight->getEstimatedDistance()) + "km - " +
                                 "Flight number " + flight->getFlightNumber())
                    ->setClassPrices(prices[TravelClass::FirstClass], prices[TravelClass::Business], prices[TravelClass::Economy]);
        }

    }

    void DepartureController::requestView(uint value, FactoryObject*& mainView, Session*& session) {
        if(value == 1) {
            DepartureView*  view    { (DepartureView*)factory->getType(DepartureView::CLASSNAME)->create() };

            if(session == nullptr) {
                throw invalid_argument("Session object cannot be null for departure-view.");
            }

            if(session->matchesOut == nullptr) {
                session->matchesOut = dbLogic->findFlight(
                            session->search.fromAirport,
                            session->search.toAirport,
                            session->search.fromDate);
            }

            if(session->matchesOut->size() == 0) {
                throw invalid_argument("No depatures found");
            }

            populateView(view->getJourneyOut(), session->search.fromAirport, session->search.toAirport, session->matchesOut);

            if(!session->search.oneWay) {
                if(session->matchesBack == nullptr) {
                    session->matchesBack = dbLogic->findFlight(
                                session->search.toAirport,
                                session->search.fromAirport,
                                session->search.toDate);
                }

                if(session->matchesBack->size() == 0) {
                    throw invalid_argument("No return flights found");
                }

                populateView(view->getJourneyBack(), session->search.toAirport, session->search.fromAirport, session->matchesBack);
            }

            mainView = view;
        }
    }

    void DepartureController::getView(JourneyContainer* journey, Session::ChosenJourney* picked, QVector<Flight*>* matches, bool ret) {
        uint    fId     { journey->getJourneySelected() };
        int     fClass  { journey->getTravelClassSelected() };

        if(fId == 0) {
            string msg = (!ret ? "departure." : "return flight.");
            throw invalid_argument("Please select a " + msg);
        }

        Flight* f{ nullptr };
        for(auto p = matches->begin(); p != matches->end(); ++p) {
            if((*p)->getId() == fId )
                f = (*p);
        }

        picked->flightId = f;
        picked->travelClass = (TravelClass)fClass;
    }

    void DepartureController::validateResult(uint value, FactoryObject*& mainView, Session*& session) {
        if(value == 1 && mainView->getInstanceName() == DepartureView::CLASSNAME) {
            DepartureView*  view    { (DepartureView*)mainView };

            getView(view->getJourneyOut(), &(session->journeyOut), session->matchesOut, false);

            if(!session->search.oneWay) {
                getView(view->getJourneyBack(), &(session->journeyBack), session->matchesBack, true);
            }
        }
    }

}
