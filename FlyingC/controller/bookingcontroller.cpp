#include "bookingcontroller.h"

namespace Controller {

    BookingController::BookingController():
        factory     { Factory::getInstance() },
        dbLogic     { DataAccessStub::getInstance() } {}

    void BookingController::requestView(uint value, FactoryObject*& mainView, Session*& session) {
        if(value == 2) {
            BookingView*  view { (BookingView*)factory->getType(BookingView::CLASSNAME)->create() };

            if(session->travellers == nullptr){
                for(int i=1; i<=session->search.adultAmount; i++){
                    view->addMember("Adult", i);
                }
                for(int i=1; i<=session->search.kidsAmount; i++){
                    view->addMember("Kid", i);
                }
                for(int i=1; i<=session->search.infantsAmount; i++){
                    view->addMember("Infant", i);
                }
            }
            else {
                for(Session::Traveller* traveller : *(session->travellers)) {
                    Member* m = new Member(traveller->ageGroup, 0);
                    m->setFirstname(traveller->firstname);
                    m->setLastname(traveller->lastname);
                    m->setBirthDate(traveller->birthofDate);
                    m->setGender(traveller->gender);

                    view->addMemberObject(m);
                }
                // Populate the view with stored information...
            }
            mainView = view;
        }
    }

    void BookingController::validateResult(uint value, FactoryObject*& mainView, Session*& session) {
        if(value == 2 && mainView->getInstanceName() == BookingView::CLASSNAME) {
            BookingView*        view    { (BookingView*)mainView };
            QVector<Member*>    members { view->getMemberVector() };

            if(session->travellers != nullptr) {
                delete(session->travellers);
            }

            session->travellers = new QVector<Session::Traveller*>;

            for(Member* m : members) {
                Session::Traveller* traveller = new Session::Traveller;
                try {
                    traveller->ageGroup     = m->getAgeGroup();
                    traveller->firstname    = m->getFirstname();
                    traveller->lastname     = m->getLastname();
                    traveller->birthofDate  = m->getBirthDate();
                    traveller->gender       = m->getGender();
                    traveller->validate();

                    session->travellers->append(traveller);
                }
                catch(invalid_argument eh){
                    throw;
                }
            }

        }
    }

}
