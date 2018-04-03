#ifndef SEARCHBARCONTROLLER_H
#define SEARCHBARCONTROLLER_H

#include "ichainhandler.h"
#include "model/factory.h"
#include "model/dalstub.h"
#include "view/searchbar.h"

using namespace DAL;
using namespace View;

namespace Controller {

    class SearchBarController : public IChainHandler<FactoryObject, Session> {

        Factory*            factory     { nullptr };
        IDataAccess*        dbLogic     { nullptr };
        SearchBar*          view        { nullptr };

    public:
        SearchBarController();
        SearchBar*  getConnectedView();

        virtual void requestView(uint , FactoryObject*& , Session*& ) override;
        virtual void validateResult(uint value, FactoryObject*& mainView, Session*& session) override;

    };
}


#endif // SEARCHBARCONTROLLER_H
