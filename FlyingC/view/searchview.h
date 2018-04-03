#ifndef SEARCHVIEW_H
#define SEARCHVIEW_H

#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QRadioButton>
#include <QSpinBox>
#include <QDate>
#include <QDateEdit>
#include "model/factoryobject.h"

namespace View {

    class SearchView : public FactoryObject {
        Q_OBJECT

        QLabel* headerTitleL {nullptr};

        QLabel*         fromLabel {nullptr};
        QComboBox*      fromDropdown {nullptr};
        QLabel*         toLabel {nullptr};
        QComboBox*      toDropdown {nullptr};
        QRadioButton*   radioRoundTrip {nullptr};
        QRadioButton*   radioOneWay {nullptr};

        QDateEdit*      fromDateLineEdit {nullptr};
        QDateEdit*      toDateLineEdit {nullptr};

        QLabel*         fromDate {nullptr};
        QPushButton*    fromButton {nullptr};

        QLabel*         toDate {nullptr};
        QPushButton*    toDateSelect {nullptr};

        QLabel*         adultsLabel {nullptr};
        QSpinBox*       adultsSpinBox {nullptr};
        QLabel*         kidsLabel {nullptr};
        QSpinBox*       kidsSpinBox {nullptr};
        QLabel*         infantsLabel {nullptr};
        QSpinBox*       infantsSpinBox {nullptr};

        QPushButton*    searchButton {nullptr};

    public:
        constexpr static const char* CLASSNAME { "SearchView" };

        SearchView();

        virtual FactoryObject* create() override;

        QWidget* createSearchGrid();
        void    addFromAirport(QString airport, QString id);
        void    addToAirPort(QString airport, QString id);
        QString getChoosenToAirport();
        QString getChoosenFromAirport();
        QDate   getFromDate();
        QDate   getToDate();
        bool    getOneWay();
        int     getAdults();
        int     getChildren();
        int     getInfants();

    private slots:
        void fromCalendar();
        void toCalendar();
        void search();

    };
}

#endif // SEARCHVIEW_H
