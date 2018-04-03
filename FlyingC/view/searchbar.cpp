#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QDebug>
#include "searchbar.h"

namespace View {

    FactoryObject* SearchBar::create() {
        return new SearchBar;
    }

    SearchBar::SearchBar() {
        setInstanceName(CLASSNAME);

        searchBox = new QLineEdit;
        searchBox->setStyleSheet("background-color:white;font-size:14px;");
        searchBox->setPlaceholderText("Search booking...");
        searchBox->setAlignment(Qt::AlignRight);
        searchBox->setTextMargins(4,4,4,4);
        searchBox->setMaximumWidth(300);
        searchBox->setMinimumHeight(28);

        searchButton = new QPushButton("Search");
        searchButton->setStyleSheet("background-color:#20b2aa;color:white;");
        searchButton->setFixedHeight(28);
        searchButton->setMaximumWidth(100);
        connect(searchButton,SIGNAL(released()),SLOT(findBooking()));

        QHBoxLayout* searchBar = new QHBoxLayout;
        searchBar->setSpacing(0);
        searchBar->setMargin(0);
        searchBar->addWidget(new QLabel);
        searchBar->addWidget(searchBox);
        searchBar->addWidget(searchButton);

        setContentsMargins(0,0,0,0);
        setStyleSheet("background-color:#3762D8;");
        setLayout(searchBar);
    }

    QString SearchBar::getSearchText() {
        return searchBox->text();
    }

    void SearchBar::findBooking() {
        setHandlerValue(10);
        callHandler();
    }
}
