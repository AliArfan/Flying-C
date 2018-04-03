#ifndef CONFIRMATIONCONTROLLER_H
#define CONFIRMATIONCONTROLLER_H

#include "ichainhandler.h"
#include "model/dalstub.h"
#include "model/factory.h"
#include "model/factoryobject.h"
#include "view/confirmationview.h"

using namespace DAL;
using namespace View;

namespace Controller {

    class ConfirmationController : public IChainHandler<FactoryObject, Session> {

        Factory*        factory { nullptr };
        IDataAccess*    dbLogic { nullptr };

    public:
        ConfirmationController();

        void requestView(uint value, FactoryObject*& mainView, Session*& session) override;
        void validateResult(uint value, FactoryObject*& mainView, Session*& session) override;
    };

}

#endif // CONFIRMATIONCONTROLLER_H
