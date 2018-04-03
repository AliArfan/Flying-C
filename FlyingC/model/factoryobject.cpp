#include "factoryobject.h"


/*
 *What the factoryobject must contain when its saved in the factory.
*/

void FactoryObject::setInstanceName(QString name) {
    instanceName = name;
}

QString FactoryObject::getInstanceName() {
    return instanceName;
}

void FactoryObject::setHandler(FactoryHandler *handler, int value) {
    this->handler = handler;
    this->value = value;
}

void FactoryObject::callHandler() const {
    if (handler)
        handler->handleResult(value);
}

void FactoryObject::setHandlerValue(int value) {
    this->value = value;
}

int FactoryObject::getHandlerValue() const {
    return value;
}

