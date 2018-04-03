#include "searchcontroller.h"
#include "view/searchview.h"

using namespace View;

namespace Controller {

    SearchController::SearchController() :
        factory     { Factory::getInstance() },
        dbLogic     { DataAccessStub::getInstance() } {
    }

    void SearchController::requestView(uint value, FactoryObject*& mainView, Session*& session) {
        if(value == 0) {
            SearchView*         view    { (SearchView*)factory->getType(SearchView::CLASSNAME)->create() };
            QVector<Airport*>   airport { dbLogic->getAllAirports() };

            for(auto i = airport.begin(); i !=airport.end(); ++i){
                view->addFromAirport((*i)->getName(), (*i)->getIataCode());
                view->addToAirPort((*i)->getName(), (*i)->getIataCode());
            }

            mainView = view;
        }
    }

    void SearchController::validateResult(uint value, FactoryObject*& mainView, Session*& session) {
        if(value == 0 && mainView->getInstanceName() == SearchView::CLASSNAME) {
            SearchView* view { (SearchView*)mainView };

            session = new Session();
            session->search.fromAirport     = view->getChoosenFromAirport();
            session->search.toAirport       = view->getChoosenToAirport();
            session->search.oneWay          = view->getOneWay();
            session->search.fromDate        = view->getFromDate();
            session->search.toDate          = view->getToDate();
            session->search.adultAmount     = view->getAdults();
            session->search.kidsAmount      = view->getChildren();
            session->search.infantsAmount   = view->getInfants();

            try {
                session->search.validate();
            }
            catch(invalid_argument eh) {
                delete session;
                session = nullptr;
                throw;
            }
        }
    }
}
