#ifndef BOOKING_H
#define BOOKING_H

#include <QVector>
#include <QString>
#include <QDateTime>
#include "ticket.h"
#include "session.h"
namespace Model {


    class Booking {
        const QString   bookingCode;
        const QDateTime orderDate;
        const QString   ccType;
        const QString   ccNumber;
        const QString   ccv;
        const QString   ccHolder;
        const QDate     ccExpiration;

        Session*        session;
        QVector<Ticket*> tickets;
    public:
        Booking(QString bookingCode, QString ccType, QString ccNumber, QString ccv, QString ccHolder, QDate ccExpiration);
        void                setSession(Session* session);
        Session*            getSession();
        QString             getBookingCode() const;
        QDateTime           getOrderDate() const;
        QString             getCCType() const;
        QString             getCCNumber() const;
        QString             getCCV() const;
        QString             getCCHolder() const;
        QDate               getCCExpiration() const;
        QVector<Ticket*>    getTickets() const;
        void                addTicket(Ticket* ticket);
         QString static generateBookingcode();
    };

}

#endif // BOOKING_H
