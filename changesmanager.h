#ifndef CHANGESMANAGER_H
#define CHANGESMANAGER_H

#include <QList>
#include <QMap>
#include <QDate>
#include <QJsonObject>

class Change;

class ChangesManager
{
public:
    ChangesManager();

    static Change* createChange(QString objectUUID, QString uuid, QString property, QVariant value, QDate date);
    static Change* fromObjectUUID(QString objectUUID, QString property);
    static QList<Change*> fromDate(QDate date);

    /**
     * @brief Sets all variables to values read from the QJsonObject, if they exist, supplied by the `DataManager`.
     * @param A reference to a QJsonObject read from a file.
     */
    static void read(const QJsonObject &json);
    /**
     * @brief Writes all variables to a QJsonObject to be written to a file later by the `DataManager`.
     * @param A reference to a QJsonObject that is to be written to a file.
     */
    static void write(QJsonObject &json);

    static void reindex();

private:

    static QList<Change> _changes;
    /**
     * @brief Maps ObjectUUIDs to property to change
     */
    static QMap<QString, QMap<QString, Change*>> _objectUUIDMap;
    static QMap<QDate, QList<Change*>> _dateMap;

    static void index(Change* change);

};

#endif // CHANGESMANAGER_H
