#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cadet.h"
#include "supplyitem.h"

#include <QFile>
#include <QJsonDocument>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
