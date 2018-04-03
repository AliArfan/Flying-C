#include "view/searchview.h"
#include "model/factory.h"
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QRadioButton>
#include <QSpinBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QHBoxLayout>
#include <Qdebug>
#include "view/calendar.h"

namespace View {

    /*
        Search view: the first view that shows up when the user runs the application. Here you can select your depature and destination, aslong as with prefered dates and amount of traveleres.
    */

    FactoryObject* SearchView::create() {
        return new SearchView();
    }

    SearchView::SearchView() {
        setInstanceName(CLASSNAME);

        headerTitleL = new QLabel("FlyingC - C you soon!");
        headerTitleL->setStyleSheet("background-color:#20b2aa;color:white;font-size:21px;font-weight:bold");
        headerTitleL->setAlignment(Qt::AlignCenter);
        headerTitleL->setMargin(16);

        QVBoxLayout* layout = new QVBoxLayout;
        layout->setSpacing(2);
        layout->setMargin(2);
        layout->addWidget(headerTitleL);
        layout->addWidget(createSearchGrid());

        setStyleSheet("background-color:#fff;line-height:1.4;");
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        setLayout(layout);
    }


    QWidget* SearchView::createSearchGrid() {
        // main content widget
        QWidget* widget = new QWidget();
        widget->setStyleSheet("background-color: #eff9ff");
        widget->setFixedWidth(500);

        QVBoxLayout* boxLayout = new QVBoxLayout();

        QHBoxLayout* HBoxLayout1 = new QHBoxLayout();
        QHBoxLayout* HBoxLayout2 = new QHBoxLayout();

        fromLabel = new QLabel("From");
        fromLabel->setStyleSheet("font-weight: bold;");
        fromDropdown = new QComboBox();
        fromDropdown->setFixedWidth(150);
        fromDropdown->setStyleSheet("background-color: #fff");

        toLabel = new QLabel("To");
        toLabel->setStyleSheet("font-weight: bold;");
        toDropdown = new QComboBox;
        toDropdown->setFixedWidth(150);
        toDropdown->setStyleSheet("background-color: #fff");

        HBoxLayout1->addWidget(fromLabel,0,Qt::AlignLeft);
        HBoxLayout1->addWidget(toLabel,0,Qt::AlignLeft);
        HBoxLayout2->addWidget(fromDropdown,0,Qt::AlignLeft);
        HBoxLayout2->addWidget(toDropdown,0,Qt::AlignLeft);


        QHBoxLayout* HBoxLayout3 = new QHBoxLayout();

        radioRoundTrip = new QRadioButton("Round trip");
        radioRoundTrip->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        radioOneWay = new QRadioButton("One way");
        radioOneWay->setChecked(true);

        HBoxLayout3->addWidget(radioRoundTrip,0,Qt::AlignLeft);
        HBoxLayout3->addWidget(radioOneWay,0,Qt::AlignLeft);

        QGridLayout* dateLayout= new QGridLayout;
        dateLayout->setHorizontalSpacing(16);
        dateLayout->setVerticalSpacing(2);

        QHBoxLayout* fromlayout= new QHBoxLayout;

        fromDate = new QLabel("Fly out");
        fromDate->setStyleSheet("font-weight: bold;");
        fromDateLineEdit= new QDateEdit;
        fromDateLineEdit->setDate(QDate::currentDate());
        fromButton= new QPushButton("📆");
        fromDateLineEdit->setStyleSheet("background-color: #fff;");
        fromDateLineEdit->setFixedWidth(110);
        fromButton->setFixedWidth(50);
        fromButton->setStyleSheet("background-color: #fff; margin-left: 5px;");
        connect(fromButton,SIGNAL(clicked()),this,SLOT(fromCalendar()));

        fromlayout->addWidget(fromDateLineEdit,0,Qt::AlignLeft);
        fromlayout->addWidget(fromButton,0,Qt::AlignLeft);
        dateLayout->addWidget(fromDate,0,0);
        dateLayout->addLayout(fromlayout,1,0);

        QHBoxLayout* tolayout= new QHBoxLayout;
        toDate = new QLabel("Fly back");
        toDate->setStyleSheet("font-weight: bold;");
        toDateLineEdit= new QDateEdit;
        toDateLineEdit->setDate(QDate::currentDate().addDays(1));
        toDateSelect= new QPushButton("📆");
        toDateLineEdit->setStyleSheet("background-color: #fff;");
        toDateLineEdit->setFixedWidth(110);
        toDateSelect->setFixedWidth(50);
        toDateSelect->setStyleSheet("background-color: #fff; margin-left: 3px;");
        connect(toDateSelect,SIGNAL(clicked()),this,SLOT(toCalendar()));

        dateLayout->addWidget(toDate,0,1);
        tolayout->addWidget(toDateLineEdit,0,Qt::AlignLeft);
        tolayout->addWidget(toDateSelect,0,Qt::AlignLeft);

        dateLayout->addLayout(tolayout,1,1);

        QGridLayout* travelers = new QGridLayout;
        travelers->setHorizontalSpacing(16);
        travelers->setVerticalSpacing(2);


        adultsLabel= new QLabel("Adult");
        adultsLabel->setStyleSheet("font-weight: bold;");
        adultsSpinBox= new QSpinBox;
        adultsSpinBox->setValue(1);
        adultsSpinBox->setStyleSheet("background-color: #fff");
        travelers->addWidget(adultsLabel,1,0);
        travelers->addWidget(adultsSpinBox,2,0);

        kidsLabel = new QLabel("Kids");
        kidsLabel->setStyleSheet("font-weight: bold;");
        kidsSpinBox = new QSpinBox;
        kidsSpinBox->setStyleSheet("background-color: #fff");
        travelers->addWidget(kidsLabel,1,1);
        travelers->addWidget(kidsSpinBox,2,1);

        infantsLabel = new QLabel("Infants");
        infantsLabel->setStyleSheet("font-weight: bold;");
        infantsSpinBox = new QSpinBox;
        infantsSpinBox->setStyleSheet("background-color: #fff");
        travelers->addWidget(infantsLabel,1,2);
        travelers->addWidget(infantsSpinBox,2,2);

        searchButton = new QPushButton("Search");
        searchButton->setStyleSheet("background-color: #3762d8; color: #fff;"
                                    "font-size:16px; height: 40px; margin-top:20px;");
        connect(searchButton,SIGNAL(clicked()),this,SLOT(search()));

        // main layout of the content
        boxLayout->addLayout(HBoxLayout1);
        boxLayout->addLayout(HBoxLayout2);
        boxLayout->addLayout(HBoxLayout3);
        boxLayout->addLayout(dateLayout);
        boxLayout->addLayout(travelers);
        boxLayout->addStretch();
        boxLayout->addWidget(searchButton);
        boxLayout->addStretch();

        widget->setLayout(boxLayout);

        return widget;
    }

    void SearchView::search() {
        this->callHandler();
    }

    void SearchView::fromCalendar(){
        Calendar calendar;
        if( calendar.exec() == QDialog::Accepted) {
            fromDateLineEdit->setDate(calendar.getDate());
        }
    }

    void SearchView::toCalendar(){
        Calendar calendar;
        if( calendar.exec() == QDialog::Accepted){
            toDateLineEdit->setDate(calendar.getDate());
        }
    }

    void SearchView::addFromAirport(QString airport, QString id){
        this->fromDropdown->addItem(airport, id);
    }

    void SearchView::addToAirPort(QString airport, QString id){
        this->toDropdown->addItem(airport, id);
    }

    QString SearchView::getChoosenToAirport(){
        return this->toDropdown->itemData((this->toDropdown->currentIndex()), Qt::UserRole).toString();
    }

    QString SearchView::getChoosenFromAirport(){
        return this->fromDropdown->itemData((this->fromDropdown->currentIndex()), Qt::UserRole).toString();
    }

    QDate SearchView::getFromDate(){
        return fromDateLineEdit->date();
    }

    QDate SearchView::getToDate(){
        return toDateLineEdit->date();
    }

    bool SearchView::getOneWay(){
        return radioOneWay->isChecked();
    }

    int SearchView::getAdults(){
        return adultsSpinBox->value();
    }

    int SearchView::getChildren(){
        return kidsSpinBox->value();
    }

    int SearchView::getInfants(){
        return infantsSpinBox->value();
    }


}
