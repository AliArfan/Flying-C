#-------------------------------------------------
#
# Project created by QtCreator 2018-04-10T11:34:10
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FlyingC
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    controller/maincontroller.cpp \
    model/aircraft.cpp \
    model/airport.cpp \
    model/booking.cpp \
    model/dalstub.cpp \
    model/factory.cpp \
    model/factoryobject.cpp \
    model/flight.cpp \
    model/flightfare.cpp \
    model/ticket.cpp \
    view/calendar.cpp \
    view/mainwindow.cpp \
    view/paymentview.cpp \
    view/searchview.cpp \
    view/confirmationview.cpp \
    model/session.cpp \
    view/departureview.cpp \
    controller/searchcontroller.cpp \
    controller/departurecontroller.cpp \
    controller/bookingcontroller.cpp \
    controller/paymentcontroller.cpp \
    controller/confirmationcontroller.cpp \
    view/bookingview.cpp \
    view/searchbar.cpp \
    controller/searchbarcontroller.cpp

HEADERS += \
    controller/maincontroller.h \
    model/aircraft.h \
    model/airport.h \
    model/booking.h \
    model/dalstub.h \
    model/factory.h \
    model/factoryobject.h \
    model/flightfare.h \
    model/flight.h \
    model/idal.h \
    model/ticket.h \
    view/calendar.h \
    view/departureview.h \
    view/mainwindow.h \
    view/paymentview.h \
    view/searchview.h \
    view/confirmationview.h \
    model/session.h \
    controller/searchcontroller.h \
    controller/ichainhandler.h \
    controller/departurecontroller.h \
    controller/bookingcontroller.h \
    controller/paymentcontroller.h \
    controller/confirmationcontroller.h \
    view/bookingview.h \
    view/searchbar.h \
    controller/searchbarcontroller.h


RESOURCES += \
    resources.qrc

