#include <QDebug>
#include "view/paymentview.h"
#include "paymentcontroller.h"

using namespace View;


namespace  Controller {


    PaymentController::PaymentController():
        factory     { Factory::getInstance() },
        dbLogic     { DataAccessStub::getInstance() } {}

    void PaymentController::requestView(uint value, FactoryObject *&mainView, Session *&session) {
        if(value == 3 ){
            PaymentView* view = (PaymentView*)factory->getType(PaymentView::CLASSNAME)->create();

            if(session->paymentDetail.cardHolder.isEmpty()) {

                Flight* flight= session->journeyOut.flightId;
                TravelClass& travel= session->journeyOut.travelClass;

                view->addSummaryWidget(view->createSummaryPaymentWidget(
                                           session->search.adultAmount,
                                           session->search.kidsAmount,
                                           session->search.infantsAmount,
                                           (flight->getFlightFare()[travel])->getPriceAdult(),
                                           (flight->getFlightFare()[travel])->getPriceChild(),
                                           (flight->getFlightFare()[travel])->getPriceBaby(),
                                           (flight->getOrigin().getName()),
                                           (flight->getDestination().getName()),
                                           (flight->getDepature())));

                if(!session->search.oneWay) {
                    Flight* flight= session->journeyBack.flightId;
                    TravelClass& travel= session->journeyBack.travelClass;

                    view->createBackPaymentWidget(
                                session->search.adultAmount,
                                session->search.kidsAmount,
                                session->search.infantsAmount,
                                ((flight->getFlightFare()[travel])->getPriceAdult()),
                                ((flight->getFlightFare()[travel])->getPriceChild()),
                                ((flight->getFlightFare()[travel])->getPriceBaby()),
                                (flight->getOrigin().getName()),
                                (flight->getDestination().getName()),
                                (flight->getDepature()));
                }
            }
            mainView=view;
        }
    }

    Ticket* PaymentController::generateTicket(QString bookingRef, Session::ChosenJourney journey, Session::Traveller* traveller) {
        TravelClass pickedClass { journey.travelClass };
        FlightFare* prices      { journey.flightId->getFlightFare()[pickedClass] };
        QString ageGroup        { traveller->ageGroup.split(':', QString::SkipEmptyParts)[0] };
        uint price              { 0 };

        if(ageGroup == "Adult")
            price = prices->getPriceAdult();
        if(ageGroup == "Kid")
            price = prices->getPriceChild();
        if(ageGroup == "Infant")
            price = prices->getPriceBaby();

       return new Ticket(bookingRef, journey.flightId->getId(), traveller->firstname, traveller->lastname, price, pickedClass);
    }

    void PaymentController::validateResult(uint value, FactoryObject *&mainView, Session *&session) {
        if(value == 3 && mainView->getInstanceName() == PaymentView::CLASSNAME) {
            PaymentView* view { (PaymentView*)mainView };

            try {
                session->paymentDetail.cardHolder=view->getCardHolder();
                session->paymentDetail.cardType=view->getCardType();
                session->paymentDetail.cardNumber=view->getCardNumber();
                session->paymentDetail.ccv=view->getCCV();
                session->paymentDetail.expiryDate=view->getCardExpiry();
                session->paymentDetail.validate();

                QString bookingRef { dbLogic->generateUniqueBookingcode() };

                Booking* booking {
                    new Booking(bookingRef,
                                view->getCardType(),
                                view->getCardNumber(),
                                view->getCCV(),
                                view->getCardHolder(),
                                view->getCardExpiry())
                };

                for(Session::Traveller* t: *(session->travellers)) {
                   booking->addTicket(generateTicket(bookingRef, session->journeyOut, t));
                }

                if(!session->search.oneWay){
                    for(Session::Traveller* t: *(session->travellers))
                        booking->addTicket(generateTicket(bookingRef, session->journeyBack, t));
                }

                session->bookingReference = bookingRef;
                booking->setSession(session);
                dbLogic->addBooking(booking);
            }
            catch(invalid_argument eh){
                throw;
            }
        }
    }

}
