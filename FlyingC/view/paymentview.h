#ifndef PAYMENTVIEW_H
#define PAYMENTVIEW_H

#include <QPushButton>
#include "QGridLayout"
#include <QComboBox>
#include <QLineEdit>
#include <QDateEdit>
#include <QLabel>
#include "model/factoryobject.h"

namespace View {

    class PaymentView : public FactoryObject {
        Q_OBJECT

        QHBoxLayout*    horizontalWidgetsLayout { nullptr };
        QWidget*        summaryWidget           { nullptr };

        QLabel*         cardType                { nullptr };
        QComboBox*      cardDropdown            { nullptr };
        QLabel*         expDate                 { nullptr };
        QDateEdit*      expDateDE               { nullptr };
        QLabel*         cardNumberL             { nullptr };
        QLabel*         ccvL                    { nullptr };
        QLineEdit*      cardNumberLE            { nullptr };
        QLineEdit*      ccvLE                   { nullptr };
        QLabel*         cardNameL               { nullptr };
        QLineEdit*      cardNameLE              { nullptr };

        QPushButton*    cancelButton            { nullptr };
        QPushButton*    orderButton             { nullptr };
        QGridLayout*    departureGrid           { nullptr };
        QLabel*         priceSumL               { nullptr };

        uint            sum{0};
    public:
        constexpr static const char* CLASSNAME{"PaymentView"};
        PaymentView();

        FactoryObject*  create() override;

        QWidget*        createPaymentGrid();
        QWidget*        createSummaryPaymentWidget(
                uint adults, uint childs, uint infants,uint adultprice, uint childprice,
                uint infantprice, QString depatureAirport, QString depatureDestination, QDateTime depatureTime);

        void            createBackPaymentWidget(
                uint adults, uint childs, uint infants, uint auldtprice, uint childprice,
                uint infantprice, QString depatureAirport, QString depatureDestination, QDateTime depaturetime);

        QString         getCardType();
        QDate           getCardExpiry();
        QString         getCardNumber();
        QString         getCardHolder();
        QString         getCCV();

        void            addSummaryWidget(QWidget* widget);
        void            setCardHolder(QString name);
        void            setExpirydate(QDate date);
        void            setCCV(QString ccv);
        void            setCardType(QString type);

    public slots:
        void            changeForm();
        void            order();
        void            cancel();
    };

}


#endif // PAYMENTVIEW_H
