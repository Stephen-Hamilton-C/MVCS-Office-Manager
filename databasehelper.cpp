#include "databasehelper.h"
#include "constants.h"

#include <QTableView>

DatabaseHelper::DatabaseHelper() {
    //Available drivers on Windows, QSQLITE QODBC QODBC3 QPSQL QPSQL7
    //Available drivers on Manjaro, QIBASE QSQLITE QSQLITE3 QMARIADB QMYSQL QMYSQL3 QODBC QODBC3 QPSQL QPSQL7 QTDS QTDS7 SKGSQLCIPHER QSQLCIPHER
    //QMYSQL has socket issues on Manjaro and is missing on Windows. I'm gonna stick with QSQLITE as it works on both
    //the article recommended QMYSQL
    cadetDB = QSqlDatabase::addDatabase("QSQLITE");
    cadetDB.setHostName("localhost");
    cadetDB.setDatabaseName("cadets");
    cadetDB.setUserName("office");
    cadetDB.setPassword("MAR-DC-045");
    bool ok = cadetDB.open();
    if(!ok){
        qDebug() << "database error: " << cadetDB.lastError().text();
    }
    qDebug() << "Database open success: " << ok;

    qDebug() << "Does anything else happen?";

    QSqlTableModel *model = new QSqlTableModel;
    model->setTable("cadet");
    model->select();

    qDebug() << "Got model";

    QSqlRecord record;
    record.setValue("capid", 585448);
    record.setValue("grade", "Cadet");
    record.setValue("rank", "2Lt");
    record.setValue("first-name", "Stephen");
    record.setValue("last-name", "Hamilton");
    record.setValue("flight", "STAFF");
    record.setValue("notes", "");

    qDebug() << "Got record";

    model->insertRecord(0, record);

    model->submitAll();

    QTableView *view = new QTableView;
    view->setModel(model);
    view->show();
}
