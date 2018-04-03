#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include <QPushButton>
#include <QLineEdit>
#include "model/factoryobject.h"

namespace View {

    class SearchBar : public FactoryObject {
        Q_OBJECT

        QLineEdit*          searchBox   { nullptr };
        QPushButton*        searchButton{ nullptr };

    private slots:
        void findBooking();
    public:
        constexpr static const char* CLASSNAME { "SearchBar" };
        SearchBar();

        QString getSearchText();
        virtual FactoryObject* create() override;
    };
}

#endif // SEARCHBAR_H
