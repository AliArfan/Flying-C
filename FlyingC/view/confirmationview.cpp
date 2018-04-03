#include <QStandardPaths>
#include <QFileDialog>
#include <QPrinter>
#include <QPainter>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QRadioButton>
#include <QSpinBox>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCommandLinkButton>
#include <QLineEdit>
#include <QWidget>
#include "view/confirmationview.h"
#include "model/factory.h"
#include "model/flightfare.h"

namespace View {

    FactoryObject* ConfirmationView::create() {
        return new ConfirmationView();
    }

    ConfirmationView::ConfirmationView() {
        setInstanceName(CLASSNAME);

        QVBoxLayout* mainLayout = new QVBoxLayout;
        content = new QVBoxLayout;

        QPushButton* confirmButton = new QPushButton("Finish");
        confirmButton->setStyleSheet("background-color: #3762d8; color: #fff;"
                                     "font-size:16px; height: 40px; width: 200px;");

        QPushButton* pdfButton = new QPushButton("Export PDF");
        pdfButton->setStyleSheet("background-color: #8dc2da; color: #fff;"
                                   "font-size:16px; height: 40px; width: 200px;");

        connect(pdfButton,SIGNAL(clicked()),this, SLOT(printToPdf()));
        connect(confirmButton, SIGNAL(clicked()), this, SLOT(confirm()));

        QHBoxLayout* buttonWrapper = new QHBoxLayout;
        buttonWrapper->addStretch();
        buttonWrapper->addWidget(confirmButton);
        buttonWrapper->addWidget(pdfButton);
        buttonWrapper->addStretch();

        mainLayout->addLayout(content);
        mainLayout->addLayout(buttonWrapper);

        setMinimumWidth(700);
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        setStyleSheet("background-color:#fff;line-height:1.4;");
        setLayout(mainLayout);
    }

    ConfirmationView *ConfirmationView::addTitle(QString title) {
        QLabel* header = new QLabel(title);
        header->setStyleSheet("background-color:#20b2aa;color:white;font-size:21px;font-weight:bold");
        header->setAlignment(Qt::AlignCenter);
        header->setMargin(16);
        content->addWidget(header);

        return this;
    }

    ConfirmationView *ConfirmationView::addText(QString text, bool strong) {
        QLabel* textLabel = new QLabel(text);
        textLabel->setMargin(5);
        textLabel->setAlignment(Qt::AlignCenter);
        if(strong)
            textLabel->setStyleSheet("font-size:16px; font-weight: bold; padding: 5px;");
        content->addWidget(textLabel);

        return this;
    }

    QString stripAgeGroup(QString s) {
        return s.split(':', QString::SkipEmptyParts)[0];
    }

    ConfirmationView* ConfirmationView::addBookingCode(QString bookingCode) {
        QLabel* bookingLabel = new QLabel("Your booking reference is: " + bookingCode);
        bookingLabel->setStyleSheet("background-color:#626363; color:white; font-size:16px;"
                                    "padding: 10px; font-weight: bold;");
        content->addWidget(bookingLabel);

        return this;
    }

    ConfirmationView* ConfirmationView::addFlight(Session::ChosenJourney journey,
                                     QVector<Session::Traveller*> travellers) {
        if(!flights) {
            QWidget* infoWidget = new QWidget;
//            infoWidget->setStyleSheet("background-color: #fff");
            flights = new QVBoxLayout;
            flights->setMargin(0);
            infoWidget->setLayout(flights);
            content->addWidget(infoWidget);
        }


        Flight f = *(journey.flightId);
        FlightInfo* info = new FlightInfo(f.getFlightNumber(),
                                     f.getDepature(),
                                     f.getOrigin(),
                                     f.getArrival(),
                                     f.getDestination());

        QString travelClass;
        switch(journey.travelClass) {
        case TravelClass::Economy:
            travelClass = "Econonmy";
            break;
        case TravelClass::Business:
            travelClass = "Business Class";
            break;
        case TravelClass::FirstClass:
            travelClass = "First Class";
            break;
        default:
            travelClass = "Incognito";
        }

        for (auto t : travellers) {
            info->addTraveller(t->firstname, t->lastname, stripAgeGroup(t->ageGroup), travelClass);
        }

        flights->addWidget(info);

        return this;
    }

    void ConfirmationView::confirm() {
        setHandlerValue(-1);
        callHandler();
    }

    FlightInfo::FlightInfo(QString flightNo,
                           QDateTime departureTime, Airport origin,
                           QDateTime arrivalTime, Airport destination) {
        setStyleSheet("background-color: #eff9ff");
        mainLayout = new QVBoxLayout;
        mainLayout->setMargin(0);

        QWidget* header = new QWidget;
        QHBoxLayout* headerLayout = new QHBoxLayout();
        header->setStyleSheet("background-color: silver;");
        header->setLayout(headerLayout);

        QLabel* flightLabel = new QLabel("Flight Info");
        QLabel* journeyLabel = new QLabel("From/To");
        QLabel* actionsLabel = new QLabel("Travellers");

        flightLabel->setStyleSheet("font-weight: bold;");
        journeyLabel->setStyleSheet("font-weight: bold;");
        actionsLabel->setStyleSheet("font-weight: bold;");

        headerLayout->addWidget(flightLabel);
        headerLayout->addWidget(journeyLabel);
        headerLayout->addWidget(actionsLabel);

        mainLayout->addWidget(header);

        QWidget* flightWidget = new QWidget;
        QHBoxLayout* layout = new QHBoxLayout;

        QLabel* flightInfo = new QLabel(flightNo + '\n' + departureTime.toString("dd MMMM yyyy"));
        QLabel* journey = new QLabel(departureTime.toString("HH:mm") + " " + origin.getLongName() + '\n' +
                                     arrivalTime.toString("HH:mm") + " " + destination.getLongName());

        travellersLayout = new QVBoxLayout;
        layout->addWidget(flightInfo);
        layout->addWidget(journey);
        layout->addLayout(travellersLayout);

        flightWidget->setLayout(layout);
        mainLayout->addWidget(flightWidget);
        setLayout(mainLayout);
    }

    void FlightInfo::addTraveller(QString firstName,
                                  QString lastName,
                                  QString ageGroup,
                                  QString travelClass) {
        QLabel* travellerInfo = new QLabel(firstName + " " + lastName + '\n' +
                                       ageGroup + ", " + travelClass);
        travellersLayout->addWidget(travellerInfo);
    }

    void ConfirmationView::printToPdf() {
        QString docsDir = QStandardPaths::locate(QStandardPaths::DocumentsLocation, "", QStandardPaths::LocateDirectory);
        QString filename = QFileDialog::getSaveFileName(this, "Save as...", docsDir, "PDF files (*.pdf)");

        QPrinter pdfPrinter(QPrinter::HighResolution);
        pdfPrinter.setOutputFormat(QPrinter::PdfFormat);
        pdfPrinter.setOutputFileName(filename);
        pdfPrinter.setPageMargins(12, 16, 12, 20, QPrinter::Millimeter);
        pdfPrinter.setFullPage(false);

        QPainter pdfPainter(&pdfPrinter);

        // calculate the scale factor needed
        double x = pdfPrinter.pageRect().width() / double(width());
        double y = pdfPrinter.pageRect().height() / double(height());
        double s = qMin(x,y);

        // first place the content in the middle of the page, then scale it down and translate it back into the center
        pdfPainter.translate(pdfPrinter.pageRect().x() + pdfPrinter.pageRect().width() / 2, pdfPrinter.pageRect().y() + pdfPrinter.pageRect().height() / 2);
        pdfPainter.scale(s, s);
        pdfPainter.translate(-width() / 2, -height() / 2);

        this->render(&pdfPainter);
    }
}
