#ifndef BOOKINGFORM_H
#define BOOKINGFORM_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDateEdit>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QWidget>

#include "model/factoryobject.h"

namespace View {

    class Member : public QWidget {
        Q_OBJECT

        QGridLayout *memberGrid         { nullptr };
        QLabel      *memberLabel        { nullptr };
        QLineEdit   *firstnameLinEdit   { nullptr };
        QLineEdit   *lastnameLinEdit    { nullptr };
        QComboBox   *gender             { nullptr };
        QDateEdit   *birthLineEdit      { nullptr };
    public:
        Member(QString person, int number);

        QString getFirstname();
        QString getLastname();
        QDate   getBirthDate();
        QString getGender();
        QString getAgeGroup();

        void    setFirstname(QString fname);
        void    setLastname(QString lname);
        void    setBirthDate(QDate date);
        void    setGender(QString gender);
        void    setMemberLabel(QString label);
    };


    class BookingView : public FactoryObject {
        Q_OBJECT

        QVBoxLayout*        mainLayout     { nullptr };
        QVBoxLayout*        memberContainer{ nullptr };
        QPushButton*        cancelButton   { nullptr };
        QPushButton*        continueButton { nullptr };

        QVector<Member*>    memberVector;
    private slots:
        void nextPage();
        void previousPage();
    public:
        constexpr static const char* CLASSNAME { "BookingView" };
        BookingView();

        FactoryObject*      create() override;
        Member*             addMember(QString person, int number);
        void                addMemberObject(Member* member);
        QVector<Member*>    getMemberVector();
    };

}

#endif // BOOKINGFORM_H
