#ifndef DEPARTUREVIEW_H
#define DEPARTUREVIEW_H

#include "model/factoryobject.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QPushButton>
#include <QLabel>
#include <QString>

namespace View {

    class JourneyClass : public QWidget {
        Q_OBJECT

        const int id;

        QLabel*         titleLabel          { nullptr };
        QLabel*         priceLabel          { nullptr };
        QRadioButton*   travelClassRadio    { nullptr };
        QLocale*        no                  { nullptr };
        QVBoxLayout*    mainLayout          { nullptr };
    public:
        JourneyClass(QString title, int id);
        uint            getId();
        bool            isChecked();
        JourneyClass*   setTitle(QString title);
        JourneyClass*   setPrice(uint price);
        QString         getTitle();
        void            updateRadioButton(JourneyClass *p);
    public slots:
        void radioButtonToggled();
    signals:
        void valueChanged(JourneyClass* p);
    };

    class JourneyDate : public QWidget {
        QLabel*         titleLabel      { nullptr };
        QLabel*         targetLabel     { nullptr };
        QLabel*         dateTimeLabel   { nullptr };
        QVBoxLayout*    mainLayout      { nullptr };
    public:
        JourneyDate(QString title, QString iataCode, QDateTime dateTime);
        JourneyDate*    setTitle(QString title);
        JourneyDate*    setIata(QString iataCode);
        JourneyDate*    setDate(QDateTime dateTime);
    };

    template<class X, class Y>
    class JourneyObserver {
    public:
        virtual void notify(X* journeyClass, Y* journey) = 0;
    };

    class Journey : public QWidget {
        Q_OBJECT

        JourneyObserver<JourneyClass, Journey>* observer{ nullptr };
        const uint id;

        QLabel*         summaryLabel        { nullptr };
        JourneyDate*    departureWidget     { nullptr };
        JourneyDate*    arrivalWidget       { nullptr };
        JourneyClass*   firstClassWidget    { nullptr };
        JourneyClass*   businessWidget      { nullptr };
        JourneyClass*   economyWidget       { nullptr };
        QGridLayout*    mainLayout          { nullptr };
    public:
        Journey(JourneyObserver<JourneyClass, Journey>* observer, uint id);
        uint            getId();
        Journey*        setClassPrices(uint firstClass, uint business, uint economy);
        Journey*        setSummary(QString summary);
        JourneyDate*    getDepartureWidget();
        JourneyDate*    getArrivalWidget();
        JourneyClass*   getFirstClassWidget();
        JourneyClass*   getBusinessWidget();
        JourneyClass*   getEconomyWidget();
        void            updateClassButtons(JourneyClass* p);
    public slots:
        void notifyUpdate(JourneyClass* p);
    };


    class JourneyContainer : public QWidget, public JourneyObserver<JourneyClass, Journey> {
        int                 travelClassSelected { -1 };
        uint                journeyIdSelected   { 0 };
        QVector<Journey*>   journeys;
        QLabel*             titleLabel  { nullptr };
        QVBoxLayout*        mainLayout  { nullptr };
    public:
        JourneyContainer();
        void        setTitle(QString text);
        Journey*    addJourney(uint id, QString fromIATA, QString toIATA, QDateTime departure, QDateTime arrival);
        int         getTravelClassSelected();
        uint        getJourneySelected();

        virtual void notify(JourneyClass* journeyClass, Journey* journey) override;
    };


    class DepartureView : public FactoryObject {
        Q_OBJECT

        JourneyContainer*   journeyOut      { nullptr };
        JourneyContainer*   journeyBack     { nullptr };
        QVBoxLayout*        mainLayout      { nullptr };
        QPushButton*        orderButton     { nullptr };
        QPushButton*        cancelButton    { nullptr };

        void initializeClassMembers();
    public:
        constexpr static const char* CLASSNAME { "DepartureView" };

        DepartureView();
        JourneyContainer*   getJourneyOut();
        JourneyContainer*   getJourneyBack();
        virtual FactoryObject* create() override;
    private slots:
        void cancelOrder();
        void continueOrder();
    };

}

#endif // DEPARTUREVIEW_H
