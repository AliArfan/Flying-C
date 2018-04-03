#include <QDebug>
#include <QDate>
#include "session.h"
#include <QRegularExpression>


using namespace std;

namespace Model{

    /*
     *   Stores the session information for each booking session, so information can be reterived easily. Everything is stored in a struct.
     */

    static uint uniqueSessionCounter = 1;

    Session::Session() : id{uniqueSessionCounter++} {}

    // Error checking for the informations stored.
    void Session::Search::validate() {
        if(adultAmount== 0)
            throw invalid_argument("Children or kids cannot travel alone");
        if(fromAirport == toAirport)
            throw invalid_argument("Cannot travel to and form same airport");
        if(fromDate == toDate)
            throw invalid_argument("Cannot travel to and from the same date");
        if(fromDate > toDate)
            throw invalid_argument("Cannot travel to the past");
    }

    void Session::Traveller::validate() {
        QRegularExpression re("^[a-zA-ZæøåÆØÅ ]+$");
        QRegularExpressionMatch firstnameMatch = re.match(firstname);
        QRegularExpressionMatch lastnameMatch = re.match(lastname);

        if(!firstnameMatch.hasMatch())
            throw invalid_argument("Firstname can only be letters");

        if(!lastnameMatch.hasMatch())
            throw invalid_argument("lastname can only be letters");

        if((birthofDate >=QDate::currentDate()))
            throw invalid_argument("You cannot be born today or in the future");

        if(!((gender == "male") || (gender == "female") || (gender == "other")))
            throw invalid_argument("Valid gender not selected");
    }

    void Session::PaymentDetail::validate(){
        QRegularExpression text("^[a-zA-Z\\sæøåÆØÅ]+$");
        QRegularExpressionMatch cardholderMatch=text.match(cardHolder);

        QRegularExpression numeric("^\\d{16}$");
        QRegularExpressionMatch cardnumberMatch=numeric.match(cardNumber);

        QRegularExpression ccvcode("\\d{3}");
        QRegularExpressionMatch ccvMatch =ccvcode.match(ccv);

        if(!cardholderMatch.hasMatch())
            throw invalid_argument("Cardholder's name can only be letters");

        if(!cardnumberMatch.hasMatch())
            throw invalid_argument("Cardnumber must be 16 digts");
        if(!ccvMatch.hasMatch())
            throw invalid_argument("CCV must be 3 digits");

        if(!((cardType == "VISA") || (cardType == "MasterCard")))
            throw invalid_argument("No correct cardtype selected");
        if(expiryDate <= QDate::currentDate())
            throw invalid_argument("Card is expired!");
    }

}
