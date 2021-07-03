/*
 * This file is a part of {{ dc045.manager }}.
 *
 * Developed for MVCS Office Manager.
 * See the LICENSE file at the top-level directory of this distribution for license details.
 * Licensed under the GNU General Public License V3
 * C/2Lt Stephen Hamilton, Civil Air Patrol
*/
#ifndef CHANGESMANAGER_H
#define CHANGESMANAGER_H

#include <QList>
#include <QMap>
#include <QDate>
#include <QJsonObject>

class ItemSnapshot;

class ChangesManager
{
public:

    static ItemSnapshot* createSnapshot(QString itemUUID, QString uuid, QMap<QString, QVariant> properties, QDate date);
    static QList<ItemSnapshot*> fromItemUUID(QString itemUUID);
    static QList<ItemSnapshot*> fromDate(QDate date);
    static ItemSnapshot* get(QString itemUUID, QDate date);

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

    static QList<ItemSnapshot> _snapshots;
    static QMap<QString, QList<ItemSnapshot*>> _itemUUIDMap;
    static QMap<QDate, QList<ItemSnapshot*>> _dateMap;
    static QMap<QString, QMap<QDate, ItemSnapshot*>> _masterMap;

    static void index(ItemSnapshot* change);

};

#endif // CHANGESMANAGER_H
