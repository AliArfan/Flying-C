#include "factory.h"
#include "view/bookingview.h"
#include "view/bookingview.h"
#include "view/calendar.h"
#include "view/departureview.h"
#include "view/paymentview.h"
#include "view/searchview.h"
#include "view/confirmationview.h"
#include "view/searchbar.h"

using namespace View;

/*
    Our factory which stores the views.
*/

Factory::Factory() {}

// Registeres one view in the factory.
void Factory::regType(FactoryObject* value) {
    factories[value->getInstanceName()] = value;
}

//Returns the view on specified key, if nothing is found then a nullpointer is returned.
FactoryObject* Factory::getType(QString key) {
    map<QString, FactoryObject*>::iterator p = factories.find(key);

    if (p != factories.end())
        return p->second;
    else
        return nullptr;
}

// Returns the factory together with the registered instances.
Factory* Factory::getInstance() {
    static Factory* instance{ nullptr };
    if (!instance) {
        instance = new Factory();

        instance->regType(new SearchBar);
        instance->regType(new BookingView());
        instance->regType(new DepartureView());
        instance->regType(new PaymentView());
        instance->regType(new SearchView());
        instance->regType(new ConfirmationView());
    }
    return instance;
}
