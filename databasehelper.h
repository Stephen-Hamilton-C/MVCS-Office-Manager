#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H

#include <QtSql/QSqlDatabase>

class DatabaseHelper
{
public:
    DatabaseHelper();

    QSqlDatabase cadetDB;
};

#endif // DATABASEHELPER_H
