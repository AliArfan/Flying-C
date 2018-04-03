#include "searchbarcontroller.h"

namespace Controller {

    SearchBarController::SearchBarController() :
        factory     { Factory::getInstance() },
        dbLogic     { DataAccessStub::getInstance() } {

        view = new SearchBar;
    }

    SearchBar* SearchBarController::getConnectedView() {
        return view;
    }

    // Not in use by this controller
    void SearchBarController::requestView(uint, FactoryObject*&, Session*&) {}

    void SearchBarController::validateResult(uint value, FactoryObject *&mainView, Session *&session) {
        if(value == 10) {
            Booking* booking = dbLogic->getBooking(view->getSearchText());

            if(booking == nullptr) {
                throw invalid_argument("No such booking number!");
            }
            else {
                session = booking->getSession();
            }
        }
    }

}
