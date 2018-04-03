#include "confirmationcontroller.h"

using namespace View;

namespace Controller {

    ConfirmationController::ConfirmationController() :
        factory { Factory::getInstance() },
        dbLogic { DataAccessStub::getInstance() } {
    }

    void ConfirmationController::requestView(uint value, FactoryObject *&mainView, Session *&session) {
        if(value == 4) {
            ConfirmationView* view { (ConfirmationView*)factory->getType(ConfirmationView::CLASSNAME)->create() };
            // set up view
            view->addTitle("Thank you for choosing FlyingC!")
                ->addText("You must present a valid photo ID to check in.\n"
                          "For more information on identification papers, see www.flyingc.com.\n"
                          "We also recommend that you print all travel documents for reference.")
                ->addBookingCode(session->bookingReference)
                ->addFlight(session->journeyOut, *session->travellers);
            if(!session->search.oneWay)
                view->addFlight(session->journeyBack, *session->travellers);

            mainView = view;
        }
    }

    void ConfirmationController::validateResult(uint value, FactoryObject *&mainView, Session *&session) {
        // Confirmation view has no data to validate, it's merely displaying
        // data from the flow - as such it has no need to validate results.
    }

}
