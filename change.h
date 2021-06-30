#ifndef CHANGE_H
#define CHANGE_H

#include <QString>
#include <QDateTime>
#include <QJsonObject>

class Change
{
public:
    Change();
    Change(QString objectUUID, QString uuid, QString property, QVariant value, QDate date);

    /**
     * @brief The UUID of the object this goes to
     */
    QString objectUUID;
    QString uuid;
    QString property;
    QVariant value;
    QDate date;

    /**
     * @brief Sets all variables to values read from the QJsonObject, if they exist, supplied by the `DataManager`.
     * @param A reference to a QJsonObject read from a file.
     */
    void read(const QJsonObject &json);
    /**
     * @brief Writes all variables to a QJsonObject to be written to a file later by the `DataManager`.
     * @param A reference to a QJsonObject that is to be written to a file.
     */
    void write(QJsonObject &json);
};

#endif // CHANGE_H
