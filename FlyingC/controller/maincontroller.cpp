#include <QMessageBox>
#include <QScrollArea>
#include <QVector>
#include <QDebug>
#include "controller/maincontroller.h"
#include "model/factory.h"

using namespace View;

namespace Controller {
    /*
        Our controller, this is where every event is handeled along as data is registered into the model and the views are changed
    */
    MainController::MainController(QMainWindow* mainWindow) :
        factory     { Factory::getInstance() },
        mainWindow  { mainWindow },
        dbLogic     { DataAccessStub::getInstance() },
        scroll      { new QScrollArea } {

        scroll->setAlignment(Qt::AlignCenter);
        scroll->setMinimumWidth(1000);
        scroll->setMinimumHeight(600);
        scroll->setStyleSheet("QScrollBar { background: silver; }");

        view = searchBarController.getConnectedView();
        view->setHandler(this, 10);

        QVBoxLayout* split = new QVBoxLayout;
        split->setSpacing(0);
        split->setMargin(0);
        split->addWidget(view);
        split->addWidget(scroll);

        QWidget* splitWidget = new QWidget;
        //splitWidget->setStyleSheet("border:none;");
        splitWidget->setLayout(split);

        mainWindow->setWindowTitle("Flying C++");
        mainWindow->setCentralWidget(splitWidget);
        mainWindow->show();

        //registeres a signal for when a viewchange is requested.
        connect(this,SIGNAL(requestViewChange(int)),SLOT(loadView(int)));
        //loads the first view stored in the factory.
        loadView(0);
    }

    void MainController::handleResult(int returnValue) {
        try {
            switch (returnValue) {
            case 0:
                searchController.validateResult(returnValue, view, session);
                break;
            case 1:
                departureController.validateResult(returnValue, view, session);
                break;
            case 2:
                bookingController.validateResult(returnValue, view, session);
                break;
            case 3:
                paymentController.validateResult(returnValue, view, session);
                break;
            case 4:
                 confirmationController.validateResult(returnValue, view, session);
                break;
            case 10:
                searchBarController.validateResult(returnValue, view, session);
                break;
            default:
                break;
            }
        }
        catch(invalid_argument eh) {
            showMessageBox(eh.what());
            return;
        }

        returnValue++;
        //emits a signal on view change requested.
        emit requestViewChange(returnValue);
    }

    void MainController::loadView(int value) {
        try {
            switch (value) {
            case 0:
                searchController.requestView(value, view, session);
                break;
            case 1:
                departureController.requestView(value, view, session);
                break;
            case 2:
                bookingController.requestView(value, view, session);
                break;
            case 3:
                paymentController.requestView(value, view, session);
                break;
            case 4:
            case 11:
                value = 4;
                confirmationController.requestView(value, view, session);
                break;
            default:
                break;
            }
        }
        catch(invalid_argument eh) {
            showMessageBox(eh.what());
            return;
        }

        view->setHandler(this, value);
        scroll->setWidget(view);
    }

    void MainController::showMessageBox(QString message){
        QMessageBox m;
        m.setText(message);
        m.exec();
    }
}
