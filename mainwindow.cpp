#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cadet.h"

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

    qDebug() << "Created cadet. \n" << &cadet;
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

        qDebug() << "Cadet Loaded: " << &cadet;
    }
}
