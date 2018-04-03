#ifndef FACTORYOBJECT_H
#define FACTORYOBJECT_H

#include <QWidget>
#include <QMap>

class FactoryHandler {
public:
    virtual void handleResult(int returnValue) = 0;
};

class FactoryObject : public QWidget {

    FactoryHandler* handler     { nullptr };
    int             value       { 0 };
    QString         instanceName{ "not defined" };
protected:
    virtual void    setInstanceName(QString name);
public:
    virtual FactoryObject* create() = 0;
    virtual QString getInstanceName();
    virtual void    setHandler(FactoryHandler *handler, int value);
    virtual void    setHandlerValue(int value);
    virtual void    callHandler() const;
    virtual int     getHandlerValue() const;
};

#endif // FACTORYOBJECT_H
