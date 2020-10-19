#include "databasehelper.h"

#include <QtDebug>

DatabaseHelper::DatabaseHelper() {
    //hm, check what's available on the laptop. On Windows, I have QSQLITE QODBC QODBC3 QPSQL QPSQL7
    //the article recommended QMYSQL
    cadetDB = QSqlDatabase::addDatabase("QSQLITE", "cadets");
    cadetDB.setHostName("localhost");
    cadetDB.setDatabaseName("cadets");
    cadetDB.setUserName("office");
    cadetDB.setPassword("MAR-DC-045");
    bool ok = cadetDB.open();
    if(!ok){
        qDebug() << "database error: " << cadetDB.lastError().text() << "\n";
    }
    qDebug() << "Database open success: " << ok << "\n";
}
