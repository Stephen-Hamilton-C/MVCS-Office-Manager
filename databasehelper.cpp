#include "databasehelper.h"

#include <QtDebug>

DatabaseHelper::DatabaseHelper() {
    //Available drivers on Windows, QSQLITE QODBC QODBC3 QPSQL QPSQL7
    //Available drivers on Manjaro, QIBASE QSQLITE QSQLITE3 QMARIADB QMYSQL QMYSQL3 QODBC QODBC3 QPSQL QPSQL7 QTDS QTDS7 SKGSQLCIPHER QSQLCIPHER
    //QMYSQL has socket issues on Manjaro and is missing on Windows. I'm gonna stick with QSQLITE as it works on both
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
