#ifndef PAYMENTCONTROLLER_H
#define PAYMENTCONTROLLER_H

#include "ichainhandler.h"
#include "model/factory.h"
#include "model/dalstub.h"

using namespace DAL;

namespace Controller {


    class PaymentController : public IChainHandler<FactoryObject, Session> {

        Factory*            factory     { nullptr };
        IDataAccess*        dbLogic     { nullptr };

        Ticket* generateTicket(QString bookingRef, Session::ChosenJourney journey, Session::Traveller* traveller);
    public:
        PaymentController();
        virtual void requestView(uint value, FactoryObject*& mainView, Session*& session) override;
        virtual void validateResult(uint value, FactoryObject*& mainView, Session*& session) override;
    };

}
#endif // PAYMENTCONTROLLER_H
