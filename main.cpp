#include "mainwindow.h"
#include "databasehelper.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    DatabaseHelper helper = DatabaseHelper();

    return a.exec();
}
