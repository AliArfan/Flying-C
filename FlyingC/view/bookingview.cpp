#include "view/bookingview.h"
#include "model/factory.h"

namespace View {

    // View of the form where the travelers fill their information.
    FactoryObject* BookingView::create() {
        return new BookingView();
    }

    // Main layout for the booking form.
    BookingView::BookingView() {
        setInstanceName(CLASSNAME);

        cancelButton = new QPushButton("Go back");
        cancelButton->setStyleSheet("background-color:#d83b38;color:#fff;font-size:16px;height:40px;");
        connect(cancelButton, SIGNAL(clicked()), this, SLOT(previousPage()));

        continueButton = new QPushButton("Go to payment");
        continueButton->setStyleSheet("background-color:#3762d8;color:#fff;font-size:16px;height:40px;");
        connect(continueButton, SIGNAL(clicked()), this, SLOT(nextPage()));

        QHBoxLayout* buttonLayout = new QHBoxLayout;
        buttonLayout->addWidget(cancelButton);
        buttonLayout->addWidget(continueButton);

        QLabel* titleLabel = new QLabel("🐧 Travellers");
        titleLabel->setStyleSheet("background-color:#20b2aa;color:white;font-size:21px;font-weight:bold");
        titleLabel->setMinimumWidth(500);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setMargin(16);

        memberContainer = new QVBoxLayout;
        memberContainer->setSpacing(0);
        memberContainer->setMargin(2);
        memberContainer->addWidget(titleLabel);

        QWidget* memberWidget = new QWidget;
        memberWidget->setStyleSheet("background-color:#fff;color:#002a3a;");
        memberWidget->setLayout(memberContainer);

        mainLayout = new QVBoxLayout;
        mainLayout->addWidget(memberWidget);
        mainLayout->addLayout(buttonLayout);

        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        setStyleSheet("line-height:1.4;");
        setLayout(mainLayout);
    }

    // Adds a traveler member to the form.
    Member* BookingView::addMember(QString person, int number) {
        Member* temp = new Member(person, number);
        memberContainer->addWidget(temp);
        memberVector.append(temp);
        return temp;
    }

    void BookingView::addMemberObject(Member* member) {
        memberContainer->addWidget(member);
        memberVector.append(member);
    }

    QVector<Member*> BookingView::getMemberVector() {
        return memberVector;
    }

    void BookingView::nextPage() {
        this->callHandler();
    }

    void BookingView::previousPage() {
        this->setHandlerValue(getHandlerValue()-2);
        this->callHandler();
    }

    //traveler class.
    Member::Member(QString person, int number) {
        memberLabel = new QLabel(person + (number > 0 ? (": " + QString::number(number)) : ""));
        memberLabel->setStyleSheet("background-color: #626363;color:#fff;font-size:14;");
        memberLabel->setMargin(4);

        QLabel* firstname = new QLabel("First name:");
        firstnameLinEdit = new QLineEdit();

        QLabel* lastname = new QLabel("Last name:");
        lastnameLinEdit = new QLineEdit();

        QLabel* genderLabel = new QLabel("Gender:");
        gender = new QComboBox();
        gender->addItem("male");
        gender->addItem("female");
        gender->addItem("other");

        QLabel* birthLabel = new QLabel("Date of Birth:");
        birthLineEdit = new QDateEdit();

        memberGrid  = new QGridLayout;
        memberGrid->addWidget(memberLabel,0,0,1,2);
        memberGrid->addWidget(firstname,2,0);
        memberGrid->addWidget(firstnameLinEdit,3,0);
        memberGrid->addWidget(lastname,2,1);
        memberGrid->addWidget(lastnameLinEdit,3,1);
        memberGrid->addWidget(genderLabel,4,0);
        memberGrid->addWidget(gender,5,0);
        memberGrid->addWidget(birthLabel,4,1);
        memberGrid->addWidget(birthLineEdit,5,1);

        setLayout(memberGrid);
    }

    QString Member::getFirstname() {
        return firstnameLinEdit->text();
    }

    QString Member::getLastname() {
        return lastnameLinEdit->text();
    }

    QDate Member::getBirthDate() {
        return birthLineEdit->date();
    }

    QString Member::getGender() {
        return gender->itemText(gender->currentIndex());
    }

    QString Member::getAgeGroup() {
        return memberLabel->text();
    }

    void Member::setMemberLabel(QString label) {
        memberLabel->setText(label);
    }

    void Member::setFirstname(QString fname) {
        firstnameLinEdit->setText(fname);
    }

    void Member::setLastname(QString lname) {
        lastnameLinEdit->setText(lname);
    }

    void Member::setBirthDate(QDate date) {
        birthLineEdit->setDate(date);
    }

    void Member::setGender(QString gendername) {
        for(int i=0; i < gender->count(); i++) {
            if(gender->itemText(i) ==gendername) {
                gender->setCurrentIndex(i);
            }
        }
    }

}
