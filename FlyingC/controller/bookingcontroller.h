#ifndef BOOKINGCONTROLLER_H
#define BOOKINGCONTROLLER_H

#include "ichainhandler.h"
#include "model/factory.h"
#include "model/dalstub.h"
#include "view/bookingview.h"

using namespace DAL;
using namespace View;



namespace Controller {

    class BookingController:public IChainHandler<FactoryObject, Session> {

        Factory*            factory     { nullptr };
        IDataAccess*        dbLogic     { nullptr };
    public:
        BookingController();

        virtual void requestView(uint value, FactoryObject*& mainView, Session*& session) override;
        virtual void validateResult(uint value, FactoryObject*& mainView, Session*& session) override;
    };
}

#endif // BOOKINGCONTROLLER_H
