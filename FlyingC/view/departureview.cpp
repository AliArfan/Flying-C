#include <QDateTime>
#include <QLocale>
#include <QDebug>
#include "departureview.h"

namespace View {

    JourneyClass::JourneyClass(QString title, int id) : id{ id } {
        titleLabel = new QLabel(title);
        titleLabel->setStyleSheet("font-weight:bold");
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setMargin(4);

        no = new QLocale(QLocale::Norwegian, QLocale::UnitedStates);

        priceLabel = new QLabel("(not set)");
        priceLabel->setAlignment(Qt::AlignCenter);
        priceLabel->setMargin(4);

        travelClassRadio = new QRadioButton;
        connect(travelClassRadio, SIGNAL(clicked(bool)), SLOT(radioButtonToggled()));

        QHBoxLayout* box = new QHBoxLayout;
        box->addWidget(travelClassRadio);
        box->setAlignment(Qt::AlignCenter);

        mainLayout = new QVBoxLayout;
        mainLayout->addWidget(titleLabel);
        mainLayout->addLayout(box);
        mainLayout->addWidget(priceLabel);

        setLayout(mainLayout);
        setMinimumWidth(160);
    }

    uint JourneyClass::getId() {
        return id;
    }

    bool JourneyClass::isChecked() {
        return travelClassRadio->isChecked();
    }

    JourneyClass* JourneyClass::setTitle(QString title) {
        titleLabel->setText(title);
        return this;
    }

    JourneyClass* JourneyClass::setPrice(uint price) {
        priceLabel->setText(price == 0 ? "(not available)":no->toCurrencyString(price));
        setEnabled(price != 0);
        return this;
    }

    QString JourneyClass::getTitle() {
        return titleLabel->text();
    }

    void JourneyClass::updateRadioButton(JourneyClass *p) {
        if(p != this) {
            travelClassRadio->setChecked(false);
        }
    }

    void JourneyClass::radioButtonToggled() {
        emit valueChanged(this);
    }

    JourneyDate::JourneyDate(QString title, QString iataCode, QDateTime dateTime) {
        titleLabel = new QLabel(title);
        titleLabel->setStyleSheet("font-weight:bold");
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setContentsMargins(4,4,4,2);

        targetLabel = new QLabel(iataCode);
        targetLabel->setAlignment(Qt::AlignCenter);
        targetLabel->setContentsMargins(4,0,4,0);

        dateTimeLabel = new QLabel(dateTime.toString("dddd dd.MMMM\nHH.mm"));
        dateTimeLabel->setAlignment(Qt::AlignCenter);
        dateTimeLabel->setContentsMargins(4,2,4,4);

        mainLayout = new QVBoxLayout;
        mainLayout->addWidget(titleLabel);
        mainLayout->addWidget(targetLabel);
        mainLayout->addWidget(dateTimeLabel);

        setLayout(mainLayout);
        setMinimumWidth(160);
    }

    JourneyDate* JourneyDate::setTitle(QString title) {
        titleLabel->setText(title);
        return this;
    }

    JourneyDate* JourneyDate::setIata(QString iataCode) {
        targetLabel->setText(iataCode);
        return this;
    }

    JourneyDate* JourneyDate::setDate(QDateTime dateTime) {
        dateTimeLabel->setText(dateTime.toString("dddd dd.MMMM\nHH.mm"));
        return this;
    }

    Journey::Journey(JourneyObserver<JourneyClass, Journey> *observer, uint id) : observer{ observer }, id{ id } {
        summaryLabel = new QLabel;
        summaryLabel->setContentsMargins(16,4,16,4);
        summaryLabel->setStyleSheet("background-color:#626363;color:white;");

        mainLayout = new QGridLayout;
        mainLayout->setSizeConstraint(QLayout::SetFixedSize);
        mainLayout->setAlignment(Qt::AlignCenter);
        mainLayout->setContentsMargins(0,0,0,0);
        mainLayout->setSpacing(0);

        departureWidget  = new JourneyDate("Departure",  "(not set)", QDateTime());
        arrivalWidget    = new JourneyDate("Arrival",    "(not set)", QDateTime());
        firstClassWidget = new JourneyClass("First class", 2);
        businessWidget   = new JourneyClass("Business", 1);
        economyWidget    = new JourneyClass("Economy", 0);

        connect(firstClassWidget, SIGNAL(valueChanged(JourneyClass*)),SLOT(notifyUpdate(JourneyClass*)));
        connect(businessWidget, SIGNAL(valueChanged(JourneyClass*)),SLOT(notifyUpdate(JourneyClass*)));
        connect(economyWidget, SIGNAL(valueChanged(JourneyClass*)),SLOT(notifyUpdate(JourneyClass*)));

        mainLayout->addWidget(departureWidget,  0,0);
        mainLayout->addWidget(arrivalWidget,    0,1);
        mainLayout->addWidget(firstClassWidget, 0,2);
        mainLayout->addWidget(businessWidget,   0,3);
        mainLayout->addWidget(economyWidget,    0,4);
        mainLayout->addWidget(summaryLabel,     1,0,    1,5);

        setLayout(mainLayout);
    }

    uint Journey::getId() {
        return id;
    }

    Journey* Journey::setClassPrices(uint firstClass, uint business, uint economy) {
        firstClassWidget->setPrice(firstClass);
        businessWidget->setPrice(business);
        economyWidget->setPrice(economy);
        return this;
    }

    Journey* Journey::setSummary(QString summary) {
        summaryLabel->setText(summary);
        return this;
    }

    JourneyDate* Journey::getDepartureWidget() {
        return departureWidget;
    }

    JourneyDate* Journey::getArrivalWidget() {
        return arrivalWidget;
    }

    JourneyClass* Journey::getFirstClassWidget() {
        return firstClassWidget;
    }

    JourneyClass* Journey::getBusinessWidget() {
        return businessWidget;
    }

    JourneyClass* Journey::getEconomyWidget() {
        return economyWidget;
    }

    void Journey::updateClassButtons(JourneyClass *p) {
        firstClassWidget->updateRadioButton(p);
        businessWidget->updateRadioButton(p);
        economyWidget->updateRadioButton(p);
    }

    void Journey::notifyUpdate(JourneyClass* p) {
        observer->notify(p, this);
    }

    JourneyContainer::JourneyContainer() {
        titleLabel = new QLabel;
        titleLabel->setStyleSheet("background-color: #20b2aa;color:white;font-size:21px;font-weight:bold");
        titleLabel->setMinimumWidth(200);
        titleLabel->setMargin(16);

        mainLayout = new QVBoxLayout;
        mainLayout->setSizeConstraint(QLayout::SetFixedSize);
        mainLayout->setAlignment(Qt::AlignCenter);
        mainLayout->setSpacing(0);
        mainLayout->setMargin(2);
        mainLayout->addWidget(titleLabel);

        setStyleSheet("background-color:white;");
    }

    void JourneyContainer::setTitle(QString text) {
        titleLabel->setText(text);
    }

    Journey* JourneyContainer::addJourney(uint id, QString fromIATA, QString toIATA, QDateTime departure, QDateTime arrival) {
        if(layout() == nullptr) {
            setLayout(mainLayout);
        }

        Journey* journey = new Journey(this, id);
        journey->getDepartureWidget()->setIata(fromIATA);
        journey->getDepartureWidget()->setDate(departure);
        journey->getArrivalWidget()->setIata(toIATA);
        journey->getArrivalWidget()->setDate(arrival);

        journeys.append(journey);
        mainLayout->addWidget(journey);

        return journey;
    }

    int JourneyContainer::getTravelClassSelected() {
        return travelClassSelected;
    }

    uint JourneyContainer::getJourneySelected() {
        return journeyIdSelected;
    }

    void JourneyContainer::notify(JourneyClass *journeyClass, Journey *journey) {
        if(journeyClass->isChecked()) {
            travelClassSelected = journeyClass->getId();
            journeyIdSelected   = journey->getId();
        } else {
            travelClassSelected = -1;
            journeyIdSelected   = 0;
        }

        for(Journey* journey : journeys) {
            journey->updateClassButtons(journeyClass);
        }
    }

    DepartureView::DepartureView() {
        setInstanceName(CLASSNAME);
    }

    void DepartureView::initializeClassMembers() {
        journeyOut  = new JourneyContainer();
        journeyBack = new JourneyContainer();

        orderButton = new QPushButton("Go to order");
        orderButton->setStyleSheet("background-color: #3762d8; color: #fff;font-size:16px; height: 40px;");
        connect(orderButton, SIGNAL(clicked()), SLOT(continueOrder()));

        cancelButton = new QPushButton("Cancel");
        cancelButton->setStyleSheet("background-color: #d83b38; color: #fff;font-size:16px; height: 40px;");
        connect(cancelButton, SIGNAL(clicked()), SLOT(cancelOrder()));

        QHBoxLayout* btnLayout = new QHBoxLayout;
        btnLayout->addWidget(cancelButton);
        btnLayout->addWidget(orderButton);

        mainLayout  = new QVBoxLayout;
        mainLayout->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(journeyOut);
        mainLayout->addWidget(journeyBack);
        mainLayout->addLayout(btnLayout);

        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        setLayout(mainLayout);
    }

    JourneyContainer* DepartureView::getJourneyOut() {
        if(layout() == nullptr) {
            initializeClassMembers();
        }
        return journeyOut;
    }

    JourneyContainer* DepartureView::getJourneyBack() {
        if(layout() == nullptr) {
            initializeClassMembers();
        }
        return journeyBack;
    }

    FactoryObject* DepartureView::create() {
        return new DepartureView;
    }

    void DepartureView::cancelOrder() {
        setHandlerValue(getHandlerValue()-2);
        callHandler();
    }

    void DepartureView::continueOrder() {
        callHandler();
    }

}
