#ifndef DEPARTURECONTROLLER_H
#define DEPARTURECONTROLLER_H

#include "ichainhandler.h"
#include "model/factory.h"
#include "model/dalstub.h"
#include "view/departureview.h"

using namespace DAL;
using namespace View;

namespace Controller {

    class DepartureController : public IChainHandler<FactoryObject, Session> {

        Factory*            factory     { nullptr };
        IDataAccess*        dbLogic     { nullptr };

        void populateView(JourneyContainer* journey, QString fromAirport, QString toAirport, QVector<Flight*>* matches);
        void getView(JourneyContainer* journey, Session::ChosenJourney* picked, QVector<Flight*>* matches, bool ret);
    public:
        DepartureController();

        virtual void requestView(uint value, FactoryObject*& mainView, Session*& session) override;
        virtual void validateResult(uint value, FactoryObject*& mainView, Session*& session) override;
    };
}

#endif // DEPARTURECONTROLLER_H
