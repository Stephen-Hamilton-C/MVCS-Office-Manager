#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H

#include <QtSql>
#include <iostream>
#include <QDebug>
#include <QMessageBox>

class DatabaseHelper
{
public:
    DatabaseHelper();

    QSqlDatabase cadetDB;
};

#endif // DATABASEHELPER_H
