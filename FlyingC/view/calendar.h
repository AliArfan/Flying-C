#ifndef CALENDAR_H
#define CALENDAR_H

#include <QDialog>
#include <QDate>
#include <QCalendarWidget>

namespace View {


    class Calendar: public QDialog {
        Q_OBJECT

        QCalendarWidget* cal { nullptr };

    public:
        Calendar(QWidget *parent =0);

        QDate getDate();

    private slots:
        void okButtonPressed();
        void cancelButtonPressed();

    };
}
#endif // CALENDAR_H
