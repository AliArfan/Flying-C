#ifndef SEARCHCONTROLLER_H
#define SEARCHCONTROLLER_H

#include "ichainhandler.h"
#include "model/factory.h"
#include "model/dalstub.h"

using namespace DAL;

namespace Controller {

    class SearchController : public IChainHandler<FactoryObject, Session> {

        Factory*            factory     { nullptr };
        IDataAccess*        dbLogic     { nullptr };

    public:
        SearchController();

        virtual void requestView(uint value, FactoryObject*& mainView, Session*& session) override;
        virtual void validateResult(uint value, FactoryObject*& mainView, Session*& session) override;
    };
}

#endif // SEARCHCONTROLLER_H
