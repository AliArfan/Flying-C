#include <QRandomGenerator>
#include <regex>
#include <string>
#include "booking.h"

using namespace std;

namespace Model {
    /*
     * Booking object has the information about the booking. There is only one booker which cardinformation is registered, and this class holds information
     * about the tickets booked for each person.
     */

    static bool hasOnlyNumbers(QString input) {
        string  data { input.toLocal8Bit().constData() };
        smatch  matches;
        regex   pattern("^[0-9]+$");
        return regex_match(data, matches, pattern);
    }

    Booking::Booking(QString bookingCode, QString ccType, QString ccNumber, QString ccv, QString ccHolder, QDate ccExpiration) :
        bookingCode     { bookingCode },
        orderDate       { QDateTime::currentDateTime() },
        ccType          { ccType.trimmed().toUpper() },
        ccNumber        { ccNumber.trimmed() },
        ccv             { ccv.trimmed() },
        ccHolder        { ccHolder.trimmed() },
        ccExpiration    { ccExpiration } {

        //error checking.
        if(bookingCode.isEmpty())
            throw invalid_argument("Booking code must be specified.");
        if(ccType.isEmpty())
            throw invalid_argument("Creditcard type must be specified.");
        if(ccNumber.size() != 16 && !hasOnlyNumbers(ccNumber))
            throw invalid_argument("Creditcard number must be 16 digits.");
        if(ccv.size() != 3 && !hasOnlyNumbers(ccv))
            throw invalid_argument("CCV code must be 3 digits.");
        if(ccHolder.isEmpty())
            throw invalid_argument("Name of creditcard holder must be specified.");
        if(ccExpiration < QDate::currentDate())
            throw invalid_argument("Creditcard has expired!");
    }

    void Booking::setSession(Session* session) {
        this->session = session;
    }

    Session* Booking::getSession() {
        return session;
    }

    QString Booking::getBookingCode() const {
        return bookingCode;
    }

    QDateTime Booking::getOrderDate() const {
        return orderDate;
    }

    QString Booking::getCCType() const {
        return ccType;
    }

    QString Booking::getCCNumber() const {
        return "xxxx xxxx xxxx " + ccNumber.right(4);
    }

    QString Booking::getCCV() const {
        return ccv;
    }

    QString Booking::getCCHolder() const {
        return ccHolder;
    }

    QDate Booking::getCCExpiration() const {
        return ccExpiration;
    }
    //Stores the booked tickets.

    QVector<Ticket*> Booking::getTickets() const {
        return tickets;
    }

    void Booking::addTicket(Ticket *ticket) {
        tickets.append(ticket);
    }
    QString Booking::generateBookingcode(){
        QVector<char> characters{ 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9' };
        QString temp;
        for(int i=0; i < 6; i++)
            temp.append(characters[QRandomGenerator::global()->bounded(characters.size())]);
        return temp;

   }
}
