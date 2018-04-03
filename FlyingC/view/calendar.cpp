#include "view/calendar.h"
#include <QDialog>
#include <QDate>
#include <QCalendarWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QString>
#include <QDebug>
namespace View {

    /*
        Calendar dialog. Shows a widget where you can choose your desired date.
    */
    Calendar::Calendar(QWidget *parent): QDialog(parent){
        QVBoxLayout* layout= new QVBoxLayout();
        this->cal= new QCalendarWidget();
        cal ->setGridVisible(true);
        cal->setMinimumDate(QDate::currentDate());
        QPushButton* okButton= new QPushButton("Ok");
        QPushButton* cancelButton= new QPushButton("Cancel");

        connect(okButton,SIGNAL(clicked()), this, SLOT(okButtonPressed()));
        connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonPressed()));

        QHBoxLayout* hbox= new QHBoxLayout;
        hbox->addWidget(okButton);
        hbox->addWidget(cancelButton);

        layout->addWidget(cal);
        layout->addLayout(hbox);

        setLayout(layout);
    }

    void Calendar::okButtonPressed() {
        accept();
    }

    void Calendar::cancelButtonPressed() {
        this->close();
    }

    QDate Calendar::getDate(){
        return cal->selectedDate();
    }

}
