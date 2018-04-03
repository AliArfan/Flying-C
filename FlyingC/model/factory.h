#ifndef FACTORY_H
#define FACTORY_H

#include <map>
#include <QString>
#include "factoryobject.h"

using namespace std;

class Factory {

    Factory();

    map<QString, FactoryObject*> factories;

public:
    static Factory* getInstance();

    void            regType(FactoryObject* value);
    FactoryObject*  getType(QString key);
};

#endif // FACTORY_H
