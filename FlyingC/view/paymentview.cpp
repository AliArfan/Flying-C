#include "view/paymentview.h"
#include "model/factory.h"
#include <QDate>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QRadioButton>
#include <QSpinBox>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QWidget>

namespace View {

    FactoryObject* PaymentView::create() {
        return new PaymentView();
    }

    PaymentView::PaymentView() {
        setInstanceName(CLASSNAME);

        QLabel* headerTitleL = new QLabel("Payment Information");
        headerTitleL->setStyleSheet("background-color: #20b2aa;color:white;font-size:21px;font-weight:bold");
        headerTitleL->setMargin(16);

        QVBoxLayout* headerLayout = new QVBoxLayout;
        headerLayout->setSpacing(0);
        headerLayout->setMargin(0);
        headerLayout->addWidget(headerTitleL);

        QWidget* titleHeaderWidget = new QWidget;
        titleHeaderWidget->setLayout(headerLayout);

        horizontalWidgetsLayout = new QHBoxLayout;
        horizontalWidgetsLayout->setAlignment(Qt::AlignLeft);
        horizontalWidgetsLayout->setMargin(0);
        horizontalWidgetsLayout->addWidget(createPaymentGrid());

        QWidget* horizontalWidget = new QWidget;
        horizontalWidget->setLayout(horizontalWidgetsLayout);

        QVBoxLayout* mainLayout = new QVBoxLayout;
        mainLayout->setSpacing(2);
        mainLayout->setMargin(2);
        mainLayout->addWidget(titleHeaderWidget);
        mainLayout->addWidget(horizontalWidget);

        QWidget* mainWidget = new QWidget;
        mainWidget->setStyleSheet("background-color:#fff");
        mainWidget->setLayout(mainLayout);

        cancelButton = new QPushButton;
        cancelButton->setText("Cancel");
        cancelButton->setStyleSheet("background-color: #d83b38; color: #fff;font-size:16px; height: 40px; width: 100px;");
        connect(cancelButton, SIGNAL(clicked()),this, SLOT(cancel()));

        orderButton = new QPushButton;
        orderButton->setText("Complete transaction");
        orderButton->setStyleSheet("background-color: #3762d8; color: #fff;font-size:16px; height: 40px; width: 200px;");
        connect(orderButton, SIGNAL(clicked()),this, SLOT(order()));

        QHBoxLayout* buttonLayout = new QHBoxLayout;
        buttonLayout->setMargin(0);
        buttonLayout->setAlignment(Qt::AlignLeft);
        buttonLayout->addWidget(cancelButton);
        buttonLayout->addWidget(orderButton);

        QWidget* buttonWidget = new QWidget;
        buttonWidget->setStyleSheet("margin-top: 15px;");
        buttonWidget->setLayout(buttonLayout);

        QVBoxLayout* layout = new QVBoxLayout;
        layout->addWidget(mainWidget);
        layout->addWidget(buttonWidget);

        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        setStyleSheet("line-height:1.4;");
        setLayout(layout);
    }

    // Need parameters of flight information
    QWidget* PaymentView::createPaymentGrid() {
        QWidget* widget = new QWidget();
        widget->setStyleSheet("background-color: #eff9ff");
        widget->setMinimumWidth(500);

        QVBoxLayout* boxLayout = new QVBoxLayout(widget);

        cardType = new QLabel("Card type");
        cardType->setStyleSheet("font-weight: bold;");
        boxLayout->addWidget(cardType);
        cardDropdown = new QComboBox();
        cardDropdown->addItem("VISA");
        cardDropdown->addItem("MasterCard");
        cardDropdown->setEditText("VISA");
        cardDropdown->setFixedWidth(150);
        cardDropdown->setStyleSheet("background-color: #fff");
        boxLayout->addWidget(cardDropdown);
        boxLayout->addStretch();

        expDate = new QLabel("Expiration date");
        expDate->setStyleSheet("font-weight: bold;");
        boxLayout->addWidget(expDate);
        expDateDE = new QDateEdit();
        expDateDE->setDate(QDate::currentDate().addYears(1));
        expDateDE->setFixedWidth(150);
        expDateDE->setStyleSheet("background-color: #fff");
        boxLayout->addWidget(expDateDE);
        boxLayout->addStretch();

        QHBoxLayout* HBoxLayout1 = new QHBoxLayout();
        QHBoxLayout* HBoxLayout2 = new QHBoxLayout();

        cardNumberL = new QLabel("Card number");
        cardNumberL->setFixedWidth(200);
        cardNumberL->setStyleSheet("font-weight: bold;");

        ccvL = new QLabel("CCV");
        ccvL->setStyleSheet("font-weight: bold;");
        ccvL->setFixedWidth(100);

        cardNumberLE = new QLineEdit();
        cardNumberLE->setFixedWidth(200);
        cardNumberLE->setStyleSheet("background-color: #fff");
        ccvLE = new QLineEdit();
        ccvLE->setStyleSheet("background-color: #fff");
        ccvLE->setMaximumWidth(100);

        HBoxLayout1->addWidget(cardNumberL,0,Qt::AlignLeft);
        HBoxLayout1->addWidget(ccvL,0,Qt::AlignCenter);
        HBoxLayout2->addWidget(cardNumberLE,0,Qt::AlignLeft);
        HBoxLayout2->addWidget(ccvLE,0,Qt::AlignCenter);

        boxLayout->addLayout(HBoxLayout1);
        boxLayout->addLayout(HBoxLayout2);

        cardNameL = new QLabel("Cardholder's name");
        cardNameL->setStyleSheet("font-weight: bold;");
        boxLayout->addWidget(cardNameL);
        cardNameLE = new QLineEdit();
        cardNameLE->setFixedWidth(200);
        cardNameLE->setStyleSheet("background-color: #fff");
        boxLayout->addWidget(cardNameLE);
        boxLayout->addStretch();

        widget->setLayout(boxLayout);

        return widget;
    }

    QWidget* PaymentView::createSummaryPaymentWidget(
            uint adults, uint childs, uint infants, uint adultprice, uint childprice,
            uint infantprice,QString depatureAirport, QString depatureDestination, QDateTime depatureTime) {

        QLabel* title = new QLabel("Departure");
        title->setStyleSheet("font-weight: bold");
        QLabel* depatureInformation= new QLabel(
                    depatureAirport + "-" + depatureDestination + "  " +
                    depatureTime.date().toString("dd.MM.yy") +" "+depatureTime.time().toString("hh:mm"));

        QGridLayout* personGrid = new QGridLayout();

        if(adults >0 ){
            QLabel* adultsL = new QLabel("Adults: ");
            QLabel* adultsPriceL = new QLabel();
            personGrid->addWidget(adultsL,0,0);
            personGrid->addWidget(adultsPriceL,0,1);
            adultsPriceL->setText(QString::number(adults) + "x"+ QString::number(adultprice)+" kr");
        }

        if(childs > 0){
            QLabel* childrenL = new QLabel("Children: ");
            QLabel* childrenPriceL = new QLabel();
            personGrid->addWidget(childrenL,1,0);
            personGrid->addWidget(childrenPriceL,1,1);
            childrenPriceL->setText(QString::number(childs) +"x"+ QString::number(childprice)+ " kr");
        }

        if(infants > 0 ){
            QLabel* infantsL = new QLabel("Infants: ");
            QLabel* infantsPriceL = new QLabel();
            personGrid->addWidget(infantsL,2,0);
            personGrid->addWidget(infantsPriceL,2,1);
            infantsPriceL->setText(QString::number(infants) + "x"+ QString::number(infantprice)+ " kr");
        }

        sum += (adults*adultprice)+(childs*childprice)+(infants*infantprice);

        departureGrid = new QGridLayout;

        priceSumL = new QLabel("Sum: " + QString::number(sum) + " kr");
        priceSumL->setStyleSheet("font-weight: bold");

        QVBoxLayout* layout = new QVBoxLayout;
        layout->addWidget(title);
        layout->addWidget(depatureInformation);
        layout->addLayout(personGrid);
        layout->addLayout(departureGrid);
        layout->addWidget(priceSumL);

        QWidget* widget = new QWidget();
        widget->setStyleSheet("background-color: #dedfdf");
        widget->setMinimumWidth(300);
        widget->setLayout(layout);

        return widget;
    }

    void PaymentView::createBackPaymentWidget(
            uint adults, uint childs, uint infants, uint adultprice, uint childprice,
            uint infantprice, QString depatureAirport, QString depatureDestination, QDateTime depaturetime) {

        QLabel* title= new QLabel("Journey back");
        title->setStyleSheet("font-weight: bold;");

        QLabel* depatureInformation= new QLabel(
                    depatureAirport + "-" + depatureDestination + "  " +
                    depaturetime.date().toString("dd.MM.yy") +" "+depaturetime.time().toString("hh:mm"));

        QGridLayout* personGrid = new QGridLayout();
        personGrid->addWidget(title,0,0);
        personGrid->addWidget(depatureInformation,1,0);

        if(adults >0 ){
            QLabel* adultsL = new QLabel("Adults: ");
            QLabel* adultsPriceL = new QLabel();
            personGrid->addWidget(adultsL,2,0);
            personGrid->addWidget(adultsPriceL,2,1);
            adultsPriceL->setText(QString::number(adults) + "x"+ QString::number(adultprice)+" kr");
        }

        if(childs > 0){
            QLabel* childrenL = new QLabel("Children: ");
            QLabel* childrenPriceL = new QLabel();
            personGrid->addWidget(childrenL,3,0);
            personGrid->addWidget(childrenPriceL,3,1);
            childrenPriceL->setText(QString::number(childs) +"x"+ QString::number(childprice)+ " kr");
        }

        if(infants > 0 ){
            QLabel* infantsL = new QLabel("Infants: ");
            QLabel* infantsPriceL = new QLabel();
            personGrid->addWidget(infantsL,4,0);
            personGrid->addWidget(infantsPriceL,4,1);
            infantsPriceL->setText(QString::number(infants) + "x"+ QString::number(infantprice)+ " kr");
        }

        sum += (adults*adultprice)+(childs*childprice)+(infants*infantprice);
        priceSumL->setText("Sum: " + QString::number(sum) + " kr");

        QWidget* widget= new QWidget();
        widget->setLayout(personGrid);

        departureGrid->addWidget(widget);
    }

    void PaymentView::changeForm() {
        // m.changeToBookingForm()
    }

    QString  PaymentView::getCardType(){
        return this->cardDropdown->itemText(cardDropdown->currentIndex());
    }

    QDate  PaymentView::getCardExpiry(){
        return  expDateDE->date();
    }

    QString  PaymentView::getCardNumber(){
        return cardNumberLE->text();
    }

    QString  PaymentView::getCardHolder(){
        return  cardNameLE->text();
    }

    QString PaymentView::getCCV(){
        return ccvLE->text();
    }

    void PaymentView::addSummaryWidget(QWidget* widget){
        horizontalWidgetsLayout->addWidget(widget);
    }

    void PaymentView::order() {
        this->callHandler();
    }

    void PaymentView::cancel() {
        this->setHandlerValue(getHandlerValue() - 2);
        this->callHandler();
    }

    void PaymentView::setCardHolder(QString name){
        cardNameLE->setText(name);
    }

    void PaymentView::setExpirydate(QDate date){
        expDateDE->setDate(date);
    }

    void PaymentView::setCCV(QString ccv){
        ccvLE->setText(ccv);
    }

    void PaymentView::setCardType(QString type){
        for(int i=0; i < cardDropdown->count(); i++){
            if(cardDropdown->itemText(i) == type){
                cardDropdown->setCurrentIndex(i);
            }
        }
    }


}


