#include "view/mainwindow.h"
#include "controller/maincontroller.h"
#include <QApplication>
#include <QIcon>
#include <QMessageBox>

using namespace View;
using namespace Controller;

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    // sets the flght icon.
    a.setWindowIcon(QIcon(":/images/flight.png"));

    MainController m(new MainWindow);

    return a.exec();
}
