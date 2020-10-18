#include "databasehelper.h"

#include <QtDebug>

DatabaseHelper::DatabaseHelper() {
    //hm, check what's available on the laptop. On Windows, I have QSQLITE QODBC QODBC3 QPSQL QPSQL7
    //the article recommended QMYSQL
    cadetDB = QSqlDatabase::addDatabase("QMYSQL", "cadets");
    cadetDB.setHostName("localhost");
    cadetDB.setDatabaseName("cadets");
    cadetDB.setUserName("office");
    cadetDB.setPassword("MAR-DC-045");
    bool ok = cadetDB.open();
    qDebug() << "Database open success: " << ok << "\n";
}
