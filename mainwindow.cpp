#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cadet.h"
#include "supplyitem.h"
#include "constants.h"

#include <QFile>
#include <QJsonDocument>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(Constants::name);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Cadet* cadet = nullptr;

void MainWindow::on_createCadet_clicked() {
    qDebug() << "Creating cadet...";

    cadet = new Cadet(
                585448,
                Cadet::GRADE::CADET,
                Cadet::RANK::LT2ND,
                "Stephen",
                "Hamilton",
                Cadet::FLIGHT::STAFF,
                "Executive Officer\n"
                "Cyber Patriot Team Captain"
                );

    qDebug() << "Created cadet. \n" << cadet->toString();
}



void MainWindow::on_saveCadet_clicked() {
    if(cadet != nullptr){
        qDebug() << "Saving cadet...";

        QFile saveFile("cadet.json");

        if(saveFile.open(QIODevice::WriteOnly)){
            QJsonObject saveObject;
            cadet->write(saveObject);
            saveFile.write(QJsonDocument(saveObject).toJson());
            qDebug() << "Cadet saved. \n" << saveObject;
        }
    }
}

void MainWindow::on_loadCadet_clicked() {
    qDebug() << "Loading cadet...";

    QFile loadFile("cadet.json");

    if(loadFile.open(QIODevice::ReadOnly)){
        QByteArray saveData = loadFile.readAll();
        QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

        if(cadet == nullptr){
            cadet = new Cadet();
        }

        cadet->read(loadDoc.object());

        qDebug() << "Cadet Loaded: " << cadet->toString();
    }
}

SupplyItem* item = nullptr;

void MainWindow::on_createItem_clicked() {
    qDebug() << "Creating item...";

    QVariantMap prop = QVariantMap();
    prop.insert("Size", "10R");

    item = new SupplyItem("ABU Blouse", 3, 0, prop);

    qDebug() << "Created item. \n" << item->toString();
}

void MainWindow::on_saveItem_clicked() {
    if(item != nullptr){
        qDebug() << "Saving item...";

        QFile saveFile("item.json");

        if(saveFile.open(QIODevice::WriteOnly)){
            QJsonObject saveObject;
            item->write(saveObject);
            saveFile.write(QJsonDocument(saveObject).toJson());
            qDebug() << "item saved. \n" << saveObject;
        }
    }
}

void MainWindow::on_loadItem_clicked() {
    qDebug() << "Loading item...";

    QFile loadFile("item.json");

    if(loadFile.open(QIODevice::ReadOnly)){
        QByteArray saveData = loadFile.readAll();
        QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

        if(item == nullptr){
            item = new SupplyItem();
        }

        item->read(loadDoc.object());

        qDebug() << "Item Loaded: " << item->toString();
    }
}

void MainWindow::on_actionCadets_triggered() {
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() == 1 ? 0 : 1);
}

void MainWindow::on_actionSupply_triggered() {
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() == 2 ? 0 : 2);
}

void MainWindow::on_actionInspections_triggered() {
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() == 3 ? 0 : 3);
}

void MainWindow::on_actionFlights_Staff_triggered() {
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() == 4 ? 0 : 4);
}

const QString aboutHTML =
        "<HTML>"
        "<p><b>"+Constants::name+" "+Constants::version+"</b></p>\n"
        "<p>"+Constants::name+" was designed for Civil Air Patrol's Mount Vernon Composite Squadron in the National Capital Wing, but may be used for other squadrons if desired.<p>\n"
        "<p>"+Constants::name+" helps office staff keep track of supply and which cadets or senior members have taken certain items. "
        "It also can show which cadets and flights are doing well with inspections.</p>"
        "<p>"+Constants::name+" was developed as an open source project under the <a href=\"https://www.gnu.org/licenses/gpl-3.0.en.html\">GPL-3.0 License</a>.</p>"
        "<p>You can access the source code here:<br>"
        "<a href=\"https://github.com/Stephen-Hamilton-C/MVCS-Office-Manager\">https://github.com/Stephen-Hamilton-C/MVCS-Office-Manager</a></p>"
        "</HTML>";

void MainWindow::on_action_About_triggered() {
    QMessageBox::about(this, "About "+Constants::name, aboutHTML);
}

void MainWindow::on_actionAbout_Qt_triggered() {
    QApplication::aboutQt();
}
