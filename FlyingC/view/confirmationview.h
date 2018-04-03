#ifndef CONFIRMATIONVIEW_H
#define CONFIRMATIONVIEW_H

#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QDateEdit>
#include <QDateTime>

#include "model/factoryobject.h"
#include "model/session.h"

using namespace Model;

namespace View {

    class FlightInfo : public QWidget {
        Q_OBJECT

        QVBoxLayout* mainLayout         { nullptr };
        QVBoxLayout* travellersLayout   { nullptr };
    public:
        FlightInfo(QString flightNo, QDateTime departureTime, Airport origin,
                                     QDateTime arrivalTime, Airport destination);

        void addTraveller(QString firstName,
                          QString lastName,
                          QString ageGroup,
                          QString travelClass);
    };


    class ConfirmationView : public FactoryObject {
        Q_OBJECT

        QVBoxLayout* content { nullptr };
        QVBoxLayout* flights { nullptr };

    public:
        constexpr static const char* CLASSNAME { "ConfirmationView" };

        ConfirmationView();
        FactoryObject* create() override;

        ConfirmationView* addTitle(QString title);
        ConfirmationView* addText(QString text, bool strong = false);
        ConfirmationView* addBookingCode(QString bookingCode);
        ConfirmationView* addFlight(Session::ChosenJourney journey, QVector<Session::Traveller*> travellers);

    public slots:
        void confirm();
        void printToPdf();

    };
}

#endif // CONFIRMATIONVIEW_H
