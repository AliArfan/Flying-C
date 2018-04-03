#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "model/dalstub.h"
#include "model/factory.h"
#include <QMainWindow>
#include <QScrollArea>
#include <QObject>
#include <QVector>

#include "searchcontroller.h"
#include "departurecontroller.h"
#include "bookingcontroller.h"
#include "paymentcontroller.h"
#include "confirmationcontroller.h"
#include "searchbarcontroller.h"

using namespace DAL;

namespace Controller {

    class MainController : public QObject, public FactoryHandler {
        Q_OBJECT

        Factory*            factory     { nullptr };
        QMainWindow*        mainWindow  { nullptr };
        IDataAccess*        dbLogic     { nullptr };
        FactoryObject*      view        { nullptr };
        Session*            session     { nullptr };
        QScrollArea*        scroll      { nullptr };

        SearchController        searchController;
        DepartureController     departureController;
        BookingController       bookingController;
        PaymentController       paymentController;
        ConfirmationController  confirmationController;
        SearchBarController     searchBarController;

    public:
        MainController(QMainWindow* mainWindow);

        void         showMessageBox(QString message);
        virtual void handleResult(int returnValue) override;

    public slots:
        void loadView(int value);
    signals:
        void requestViewChange(int value);
    };
}

#endif // MAINCONTROLLER_H
