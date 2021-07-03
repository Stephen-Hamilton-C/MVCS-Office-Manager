#include "changesmanager.h"
#include "itemsnapshot.h"

#include <QJsonArray>

QList<ItemSnapshot> ChangesManager::_snapshots = QList<ItemSnapshot>();
QMap<QString, QList<ItemSnapshot*>> ChangesManager::_itemUUIDMap = QMap<QString, QList<ItemSnapshot*>>();
QMap<QDate, QList<ItemSnapshot*>> ChangesManager::_dateMap = QMap<QDate, QList<ItemSnapshot*>>();
QMap<QString, QMap<QDate, ItemSnapshot*>> ChangesManager::_masterMap = QMap<QString, QMap<QDate, ItemSnapshot*>>();

ItemSnapshot* ChangesManager::createSnapshot(QString itemUUID, QString uuid, QMap<QString, QVariant> properties, QDate date)
{
    if(_masterMap.contains(itemUUID) && _masterMap[itemUUID].contains(date)){
        ItemSnapshot* snapshot = _masterMap[itemUUID][date];
        snapshot->properties = properties;
        return snapshot;
    } else {
        _snapshots.append(ItemSnapshot(itemUUID, uuid, properties, date));
        ItemSnapshot* snapshot = &_snapshots.last();
        index(snapshot);
        return snapshot;
    }
}

QList<ItemSnapshot *> ChangesManager::fromItemUUID(QString itemUUID)
{
    return _itemUUIDMap[itemUUID];
}

QList<ItemSnapshot*> ChangesManager::fromDate(QDate date)
{
    return _dateMap[date];
}

ItemSnapshot* ChangesManager::get(QString itemUUID, QDate date)
{
    return _masterMap[itemUUID][date];
}

void ChangesManager::read(const QJsonObject &json)
{
    if(json.contains("changes") && json["changes"].isArray()){
        const QJsonArray jChanges = json["changes"].toArray();
        for(int i = 0; i < jChanges.count(); i++){
            ItemSnapshot snapshot;
            snapshot.read(json["changes"][i].toObject());
            _snapshots.append(snapshot);
        }
    }

    reindex();
}

void ChangesManager::write(QJsonObject &json)
{
    QJsonArray jChanges;
    for(int i = 0; i < _snapshots.count(); i++){
        QJsonObject changeJObj;
        _snapshots[i].write(changeJObj);
        jChanges.append(changeJObj);
    }

    json["changes"] = jChanges;
}

void ChangesManager::reindex()
{
    _dateMap.clear();
    _itemUUIDMap.clear();

    for(int i = 0; i < _snapshots.count(); i++){
        ItemSnapshot* snapshot = &_snapshots[i];
        index(snapshot);
    }
}

void ChangesManager::index(ItemSnapshot* snapshot)
{
    if(_dateMap.contains(snapshot->date)){
        _dateMap[snapshot->date].append(snapshot);
    } else {
        _dateMap.insert(snapshot->date, QList<ItemSnapshot*>{snapshot});
    }

    if(_itemUUIDMap.contains(snapshot->itemUUID)){
        _itemUUIDMap[snapshot->itemUUID].append(snapshot);
    } else {
        _itemUUIDMap.insert(snapshot->itemUUID, QList<ItemSnapshot*>{snapshot});
    }

    if(_masterMap.contains(snapshot->itemUUID)){
        _masterMap[snapshot->itemUUID].insert(snapshot->date, snapshot);
    } else {
        _masterMap.insert(snapshot->itemUUID, QMap<QDate, ItemSnapshot*>{{snapshot->date, snapshot}});
    }
}
